import { GlobalSettings } from "./shared";
import * as Enums from "./enums";
import { ChannelAdapter } from "./channel-adapter";
import { ActivityStatus, ActivityResponse, ActivityRequest, ActivityInvocationTrigger } from "./invoke-activity";
import { Strings } from "./strings";
import { SubmitAction, SerializationContext, CardElement, AdaptiveCard, Action, GlobalRegistry, Input } from "./card-elements";
import { Versions, property, PropertyDefinition, PropertyBag, SerializableObject, Version, SerializableObjectProperty } from "./serialization";
import { CardObjectRegistry } from "./registry";
import { HostConfig } from "./host-config";
import { ExecuteAction } from "./execute-action";

function clearElementChildren(element: HTMLElement) {
    while (element.firstChild) {
        element.removeChild(element.firstChild);
    }
}

function logEvent(level: Enums.LogLevel, message?: any, ...optionalParams: any[]) {
    if (GlobalSettings.applets.logEnabled) {
        if (GlobalSettings.applets.onLogEvent) {
            GlobalSettings.applets.onLogEvent(level, message, optionalParams);
        }
        else {
            switch (level) {
                case Enums.LogLevel.Warning:
                    console.warn(message, optionalParams);
                    break;
                case Enums.LogLevel.Error:
                    console.error(message, optionalParams);
                    break;
                default:
                    console.log(message, optionalParams);
                    break;
            }
        }
    }
}

export class RefreshActionProperty extends PropertyDefinition {
    parse(sender: RefreshDefinition, source: PropertyBag, context: SerializationContext): ExecuteAction | undefined {
        let action = context.parseAction(
            sender.parent,
            source[this.name],
            [],
            false);

        if (action && action instanceof ExecuteAction) {
            return action;
        }
        else {
            context.logParseEvent(
                sender,
                Enums.ValidationEvent.ActionTypeNotAllowed,
                "The \"refresh\" property must have its \"action\" field defined set to an Action.Execute object");

            return undefined;
        }
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: ExecuteAction | undefined, context: SerializationContext) {
        context.serializeValue(target, this.name, value ? value.toJSON(context) : undefined);
    }

    constructor(readonly targetVersion: Version, readonly name: string) {
        super(targetVersion, name, undefined);
    }
}

export class RefreshDefinition extends SerializableObject {
    //#region Schema

    static readonly actionProperty = new RefreshActionProperty(Versions.v1_0, "action");

    @property(RefreshDefinition.actionProperty)
    get action(): ExecuteAction {
        return this.getValue(RefreshDefinition.actionProperty);
    }

    set action(value: ExecuteAction) {
        this.setValue(RefreshDefinition.actionProperty, value);

        if (value) {
            value.setParent(this.parent);
        }
    }

    protected getSchemaKey(): string {
        return "RefreshDefinition";
    }

    //#endregion

    parent: CardElement;
}

export class AdaptiveAppletCard extends AdaptiveCard {
    //#region Schema

    static readonly refreshProperty = new SerializableObjectProperty(Versions.v1_0, "refresh", RefreshDefinition, true);

    @property(AdaptiveAppletCard.refreshProperty)
    get refresh(): RefreshDefinition | undefined {
        return this.getValue(AdaptiveAppletCard.refreshProperty);
    }

    set refresh(value: RefreshDefinition | undefined) {
        this.setValue(AdaptiveAppletCard.refreshProperty, value);

        if (value) {
            value.parent = this;
        }
    }

    protected getSchemaKey(): string {
        return "AdaptiveAppletCard";
    }

    //#endregion
}

export class AdaptiveApplet {
    static readonly elementsRegistry = new CardObjectRegistry<CardElement>();
    static readonly actionsRegistry = new CardObjectRegistry<Action>();

    static initialize() {
        GlobalRegistry.populateWithDefaultElements(AdaptiveApplet.elementsRegistry);
        GlobalRegistry.populateWithDefaultActions(AdaptiveApplet.actionsRegistry);

        AdaptiveApplet.actionsRegistry.unregister("Action.Submit");
        AdaptiveApplet.actionsRegistry.register("Action.Execute", ExecuteAction, Versions.v1_2);
    }

    private _card?: AdaptiveAppletCard;
    private _cardPayload: any;
    private _allowAutomaticCardUpdate: boolean = false;
    private _refreshButtonHostElement: HTMLElement;
    private _cardHostElement: HTMLElement;

    private displayCard(card: AdaptiveCard) {
        if (card.renderedElement) {
            clearElementChildren(this._cardHostElement);

            this._refreshButtonHostElement.style.display = "none";

            this._cardHostElement.appendChild(card.renderedElement);
        }
        else {
            throw new Error("displayCard: undefined card.");
        }
    }

    private displayRefreshButton(refreshAction: ExecuteAction) {
        this._refreshButtonHostElement.style.display = "none";

        let renderedRefreshButton: HTMLElement | undefined = undefined;

        if (this.onRenderRefreshButton) {
            renderedRefreshButton = this.onRenderRefreshButton(this);
        }
        else {
            let cardPayload: object;
            
            if (GlobalSettings.applets.refresh.mode === Enums.RefreshMode.Automatic) {
                let autoRefreshPausedMessage = Strings.runtime.automaticRefreshPaused();

                if (autoRefreshPausedMessage[autoRefreshPausedMessage.length - 1] !== " ") {
                    autoRefreshPausedMessage += " ";
                }

                cardPayload = {
                    type: "AdaptiveCard",
                    version: "1.2",
                    body: [
                        {
                            type: "RichTextBlock",
                            horizontalAlignment: "right",
                            inlines: [
                                autoRefreshPausedMessage,
                                {
                                    type: "TextRun",
                                    text: Strings.runtime.clckToRestartAutomaticRefresh(),
                                    selectAction: {
                                        type: "Action.Submit",
                                        id: "refreshCard"
                                    }
                                }
                            ]
                        }
                    ]
                };
            }
            else {
                cardPayload = {
                    type: "AdaptiveCard",
                    version: "1.2",
                    body: [
                        {
                            type: "RichTextBlock",
                            horizontalAlignment: "right",
                            inlines: [
                                {
                                    type: "TextRun",
                                    text: Strings.runtime.refreshThisCard(),
                                    selectAction: {
                                        type: "Action.Submit",
                                        id: "refreshCard"
                                    }
                                }
                            ]
                        }
                    ]
                };
            }

            let card = new AdaptiveCard();
            card.parse(cardPayload, new SerializationContext(Versions.v1_2));
            card.onExecuteAction = (action: Action) => {
                if (action.id === "refreshCard") {
                    clearElementChildren(this._refreshButtonHostElement);
                    
                    this.internalExecuteAction(refreshAction, ActivityInvocationTrigger.Automatic, 0);
                }
            }

            renderedRefreshButton = card.render();
        }

        if (renderedRefreshButton) {
            clearElementChildren(this._refreshButtonHostElement);

            this._refreshButtonHostElement.appendChild(renderedRefreshButton);

            this._refreshButtonHostElement.style.removeProperty("display");
        }
    }

    private createActivityRequest(action: ExecuteAction, trigger: ActivityInvocationTrigger, consecutiveRefreshes: number): ActivityRequest | undefined {
        if (this.card) {
            let request: ActivityRequest = {
                activity: {
                    type: "invoke",
                    name: "adaptiveCard/action",
                    localTimezone: "",
                    localTimestamp: "",
                    value: {
                        action: {
                            type: "Action.Execute",
                            id: action.id,
                            verb: action.verb,
                            data: action.data
                        },
                        trigger: trigger,
                    }
                },
                attemptNumber: 0,
                consecutiveRefreshes: consecutiveRefreshes,
                action: action
            };

            let cancel = this.onPrepareActivityRequest ? !this.onPrepareActivityRequest(this, action, request) : false;

            return cancel ? undefined : request;
        }
        else {
            throw new Error("createActivityRequest: no card has been set.");
        }
    }

    private createMagicCodeInputCard(attemptNumber: number): AdaptiveCard {
        let payload = {
            type: "AdaptiveCard",
            version: "1.0",
            body: [
                {
                    type: "TextBlock",
                    color: "attention",
                    text: attemptNumber === 0 ? undefined : "That didn't work... let's try again.",
                    wrap: true,
                    horizontalAlignment: "center"
                },
                {
                    type: "TextBlock",
                    text: "Please login in the popup. You will obtain a magic code. Paste that code below and select \"Submit\"",
                    wrap: true,
                    horizontalAlignment: "center"
                },
                {
                    type: "Input.Text",
                    id: "magicCode",
                    placeholder: "Enter magic code"
                },
                {
                    type: "ActionSet",
                    horizontalAlignment: "center",
                    actions: [
                        {
                            type: "Action.Submit",
                            id: "submitMagicCode",
                            title: "Submit"
                        },
                        {
                            type: "Action.Submit",
                            id: "cancel",
                            title: "Cancel"
                        },
                        {
                            type: "Action.Submit",
                            id: "wontWork",
                            title: "This won't work"
                        }
                    ]
                }
            ]
        };

        let card = new AdaptiveCard();
        card.parse(payload);

        return card;
    }

    private cancelAutomaticRefresh() {
        if (this._allowAutomaticCardUpdate) {
            logEvent(Enums.LogLevel.Warning, "Automatic card refresh has been cancelled as a result of the user interacting with the card.");
        }

        this._allowAutomaticCardUpdate = false;
    }

    private internalSetCard(payload: any, consecutiveRefreshes: number) {
        if (typeof payload === "object" && payload["type"] === "AdaptiveCard") {
            this._cardPayload = payload;
        }

        if (this._cardPayload) {
            try {
                let card = new AdaptiveAppletCard();

                if (this.hostConfig) {
                    card.hostConfig = this.hostConfig;
                }

                let serializationContext = new SerializationContext();
                serializationContext.setElementRegistry(AdaptiveApplet.elementsRegistry);
                serializationContext.setActionRegistry(AdaptiveApplet.actionsRegistry);

                card.parse(this._cardPayload, serializationContext);

                let doChangeCard = this.onCardChanging ? this.onCardChanging(this, this._cardPayload) : true;

                if (doChangeCard) {
                    this._card = card;
                    this._card.onExecuteAction = (action: Action) => {
                        // If the user takes an action, cancel any pending automatic refresh
                        this.cancelAutomaticRefresh();

                        this.internalExecuteAction(action, ActivityInvocationTrigger.Manual, 0);
                    }
                    this._card.onInputValueChanged = (input: Input) => {
                        // If the user modifies an input, cancel any pending automatic refresh
                        this.cancelAutomaticRefresh();
                    }

                    this._card.render();

                    if (this._card.renderedElement) {
                        this.displayCard(this._card);

                        if (this.onCardChanged) {
                            this.onCardChanged(this);
                        }

                        if (this._card.refresh) {
                            if (GlobalSettings.applets.refresh.mode === Enums.RefreshMode.Automatic && consecutiveRefreshes < GlobalSettings.applets.refresh.maximumConsecutiveAutomaticRefreshes) {
                                if (GlobalSettings.applets.refresh.timeBetweenAutomaticRefreshes <= 0) {
                                    logEvent(Enums.LogLevel.Info, "Triggering automatic card refresh number " + (consecutiveRefreshes + 1));

                                    this.internalExecuteAction(this._card.refresh.action, ActivityInvocationTrigger.Automatic, consecutiveRefreshes + 1);
                                }
                                else {
                                    logEvent(Enums.LogLevel.Info, "Scheduling automatic card refresh number " + (consecutiveRefreshes + 1) + " in " + GlobalSettings.applets.refresh.timeBetweenAutomaticRefreshes + "ms");

                                    let action = this._card.refresh.action;

                                    this._allowAutomaticCardUpdate = true;

                                    window.setTimeout(
                                        () => {
                                            if (this._allowAutomaticCardUpdate) {
                                                this.internalExecuteAction(action, ActivityInvocationTrigger.Automatic, consecutiveRefreshes + 1);
                                            }
                                        },
                                        GlobalSettings.applets.refresh.timeBetweenAutomaticRefreshes
                                    )
                                }
                            }
                            else if (GlobalSettings.applets.refresh.mode !== Enums.RefreshMode.Disabled) {
                                if (consecutiveRefreshes > 0) {
                                    logEvent(Enums.LogLevel.Warning, "Stopping automatic refreshes after " + consecutiveRefreshes + " consecutive refreshes.");
                                }
                                else {
                                    logEvent(Enums.LogLevel.Warning, "The card has a refresh section, but automatic refreshes are disabled.");
                                }

                                if (GlobalSettings.applets.refresh.allowManualRefreshesAfterAutomaticRefreshes || GlobalSettings.applets.refresh.mode === Enums.RefreshMode.Manual) {
                                    logEvent(Enums.LogLevel.Info, "Showing manual refresh button.");

                                    this.displayRefreshButton(this._card.refresh.action);
                                }
                            }
                        }
                    }
                }
            }
            catch (error) {
                // Ignore all errors
                logEvent(Enums.LogLevel.Error, "setCard: " + error);
            }
        }
    }

    private internalExecuteAction(action: Action, trigger: ActivityInvocationTrigger, consecutiveRefreshes: number) {
        if (action instanceof ExecuteAction) {
            if (this.channelAdapter) {
                let request = this.createActivityRequest(action, trigger, consecutiveRefreshes);

                if (request) {
                    this.internalSendActivityRequestAsync(request);
                }
            }
            else {
                throw new Error("internalExecuteAction: No channel adapter set.");
            }
        }

        if (this.onExecuteAction) {
            this.onExecuteAction(this, action);
        }
    }

    private activityRequestSucceeded(response: ActivityResponse) {
        if (this.onActivityRequestSucceeded) {
            this.onActivityRequestSucceeded(this, response);
        }
    }

    private activityRequestFailed(response: ActivityResponse): number {
        return this.onActivityRequestFailed ? this.onActivityRequestFailed(this, response) : GlobalSettings.applets.defaultTimeBetweenRetryAttempts;
    }

    private async internalSendActivityRequestAsync(request: ActivityRequest) {
        if (!this.channelAdapter) {
            throw new Error("internalSendActivityRequestAsync: channelAdapter is not set.")
        }

        let overlay = this.createProgressOverlay(request);

        if (overlay !== undefined) {
            this.renderedElement.appendChild(overlay);
        }

        const removeOverlay = () => {
            if (this.onRemoveProgressOverlay) {
                this.onRemoveProgressOverlay(this, request);
            }
            
            if (overlay !== undefined) {
                this.renderedElement.removeChild(overlay);
            }
        }

        let done = false;

        while (!done) {
            let response: ActivityResponse | undefined = undefined;

            if (request.attemptNumber === 0) {
                logEvent(Enums.LogLevel.Info, "Sending activity request to channel (attempt " + (request.attemptNumber + 1) + ")");
            }
            else {
                logEvent(Enums.LogLevel.Info, "Re-sending activity request to channel (attempt " + (request.attemptNumber + 1) + ")");
            }

            try {
                response = await this.channelAdapter.sendRequestAsync(request);
            }
            catch (error) {
                logEvent(Enums.LogLevel.Error, "Activity request failed: " + error);

                removeOverlay();

                done = true;
            }

            if (response) {
                switch (response.status) {
                    case ActivityStatus.Success:
                        removeOverlay();

                        try {
                            response.content = JSON.parse(response.content);
                        }
                        catch {
                            // Leave the content as is
                        }

                        if (typeof response.content === "string") {
                            logEvent(Enums.LogLevel.Info, "The activity request returned a string after " + (request.attemptNumber + 1) + " attempt(s).");
                        }
                        else if (typeof response.content === "object") {
                            switch (response.content["type"]) {
                                case "AdaptiveCard":
                                    logEvent(Enums.LogLevel.Info, "The activity request returned an Adaptive Card after " + (request.attemptNumber + 1) + " attempt(s).");

                                    this.internalSetCard(response.content, request.consecutiveRefreshes);

                                    break;
                                case "Activity.InvocationError.Unauthorized":
                                    logEvent(Enums.LogLevel.Info, "The activity request returned Activity.InvocationError.Unauthorized after " + (request.attemptNumber + 1) + " attempt(s).");

                                    if ((request.attemptNumber + 1) <= GlobalSettings.applets.maximumRetryAttempts) {
                                        let loginUrl: URL;

                                        try {
                                            loginUrl = new URL(response.content["loginUrl"]);
                                        }
                                        catch (e) {
                                            logEvent(Enums.LogLevel.Error, "Invalid loginUrl: " + response.content["loginUrl"]);

                                            throw e;
                                        }

                                        logEvent(Enums.LogLevel.Info, "Login required at " + loginUrl.toString());

                                        let magicCodeInputCard = this.createMagicCodeInputCard(request.attemptNumber);
                                        magicCodeInputCard.render();
                                        magicCodeInputCard.onExecuteAction = (submitMagicCodeAction: Action) => {
                                            if (this.card && submitMagicCodeAction instanceof SubmitAction) {
                                                switch (submitMagicCodeAction.id) {
                                                    case "submitMagicCode":
                                                        let magicCode: string | undefined = undefined;

                                                        if (submitMagicCodeAction.data && typeof (<any>submitMagicCodeAction.data)["magicCode"] === "string") {
                                                            magicCode = (<any>submitMagicCodeAction.data)["magicCode"];
                                                        }

                                                        if (magicCode) {
                                                            this.displayCard(this.card);

                                                            request.activity.value.magicCode = magicCode;
                                                            request.attemptNumber++;

                                                            this.internalSendActivityRequestAsync(request);
                                                        }
                                                        else {
                                                            alert("Please enter the magic code you received.");
                                                        }

                                                        break;
                                                    case "cancel":
                                                        logEvent(Enums.LogLevel.Warning, "Authentication cancelled by user.");

                                                        this.displayCard(this.card);

                                                        break;
                                                    default:
                                                        logEvent(Enums.LogLevel.Error, "Unespected action taken from magic code input card (id = " + submitMagicCodeAction.id + ")");

                                                        alert("Something went wrong. This action can't be handled.");

                                                        break;
                                                }
                                            }
                                        }

                                        this.displayCard(magicCodeInputCard);

                                        let left = window.screenX + (window.outerWidth - GlobalSettings.applets.authPromptWidth) / 2;
                                        let top = window.screenY + (window.outerHeight - GlobalSettings.applets.authPromptHeight) / 2;

                                        window.open(loginUrl.toString(), "Login", `width=${GlobalSettings.applets.authPromptWidth},height=${GlobalSettings.applets.authPromptHeight},left=${left},top=${top}`);
                                    }
                                    else {
                                        logEvent(Enums.LogLevel.Error, "Authentication failed. Giving up after " + (request.attemptNumber + 1) + " attempt(s)");

                                        alert("Authentication failed.");
                                    }

                                    break;
                                default:
                                    throw new Error("internalSendActivityRequestAsync: Action.Execute result is of unsupported type (" + typeof response.content + ")");
                            }
                        }
                        else {
                            throw new Error("internalSendActivityRequestAsync: Action.Execute result is of unsupported type (" + typeof response.content + ")");
                        }

                        this.activityRequestSucceeded(response);

                        done = true;

                        break;
                    case ActivityStatus.Failure:
                    default:
                        let retryIn: number = this.activityRequestFailed(response);

                        if (retryIn >= 0 && (request.attemptNumber + 1) < GlobalSettings.applets.maximumRetryAttempts) {
                            logEvent(Enums.LogLevel.Warning, "Activity request failed. Retrying in " + retryIn + "ms");

                            request.attemptNumber++;

                            await new Promise<void>(
                                (resolve, reject) => {
                                    window.setTimeout(
                                        () => { resolve(); },
                                        retryIn
                                    )
                                });
                        }
                        else {
                            logEvent(Enums.LogLevel.Error, "Activity request failed. Giving up after " + (request.attemptNumber + 1) + " attempt(s)");

                            removeOverlay();

                            done = true;
                        }

                        break;
                }
            }
        }
    }

    private createProgressOverlay(request: ActivityRequest): HTMLElement | undefined {
        let overlay: HTMLElement | undefined = undefined;

        if (this.onCreateProgressOverlay) {
            overlay = this.onCreateProgressOverlay(this, request);
        }
        else {
            overlay = document.createElement("div");
            overlay.className = "aaf-progress-overlay";

            let spinner = document.createElement("div");
            spinner.className = "aaf-spinner";
            spinner.style.width = "28px";
            spinner.style.height = "28px";

            overlay.appendChild(spinner);
        }

        return overlay;
    }

    readonly renderedElement: HTMLElement;

    userId?: string;
    hostConfig?: HostConfig;
    channelAdapter?: ChannelAdapter;

    onCardChanging?: (sender: AdaptiveApplet, card: any) => boolean;
    onCardChanged?: (sender: AdaptiveApplet) => void;
    onPrepareActivityRequest?: (sender: AdaptiveApplet, action: ExecuteAction, request: ActivityRequest) => boolean;
    onActivityRequestSucceeded?: (sender: AdaptiveApplet, response: ActivityResponse) => void;
    onActivityRequestFailed?: (sender: AdaptiveApplet, response: ActivityResponse) => number;
    onCreateProgressOverlay?: (sender: AdaptiveApplet, request: ActivityRequest) => HTMLElement | undefined;
    onRemoveProgressOverlay?: (sender: AdaptiveApplet, request: ActivityRequest) => void;
    onRenderRefreshButton?: (sender: AdaptiveApplet) => HTMLElement | undefined;
    onExecuteAction?: (sender: AdaptiveApplet, action: Action) => void;

    constructor() {
        this.renderedElement = document.createElement("div");
        this.renderedElement.className = "aaf-cardHost"
        this.renderedElement.style.position = "relative";
        this.renderedElement.style.display = "flex";
        this.renderedElement.style.flexDirection = "column";

        this._cardHostElement = document.createElement("div");

        this._refreshButtonHostElement = document.createElement("div");
        this._refreshButtonHostElement.className = "aaf-refreshButtonHost";    
        this._refreshButtonHostElement.style.display = "none";

        this.renderedElement.appendChild(this._cardHostElement);
        this.renderedElement.appendChild(this._refreshButtonHostElement);
    }

    refreshCard() {
        if (this._card && this._card.refresh) {
            this.internalExecuteAction(this._card.refresh.action, ActivityInvocationTrigger.Manual, 0);
        }
    }

    setCard(payload: any) {
        this.internalSetCard(payload, 0);
    }

    get card(): AdaptiveAppletCard | undefined {
        return this._card;
    }
}

AdaptiveApplet.initialize();
