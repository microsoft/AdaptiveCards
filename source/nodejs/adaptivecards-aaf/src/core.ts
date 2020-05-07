import * as Adaptive from "adaptivecards";
import * as Templating from "adaptivecards-templating";
import { ChannelAdapter } from "./channel-adapter";
import { ActivityStatus, ActivityResponse, ActivityRequest, ActivityInvocationTrigger } from "./invoke-activity";
import { Strings } from "./strings";

function clearElementChildren(element: HTMLElement) {
    while (element.firstChild) {
        element.removeChild(element.firstChild);
    }
}

function logEvent(level: LogLevel, message?: any, ...optionalParams: any[]) {
    if (GlobalSettings.logEnabled) {
        if (GlobalSettings.onLogEvent) {
            GlobalSettings.onLogEvent(level, message, optionalParams);
        }
        else {
            switch (level) {
                case LogLevel.Warning:
                    console.warn(message, optionalParams);
                    break;
                case LogLevel.Error:
                    console.error(message, optionalParams);
                    break;
                default:
                    console.log(message, optionalParams);
                    break;
            }
        }
    }
}

export enum RefreshMode {
    Disabled,
    Manual,
    Automatic
}

export enum LogLevel {
    Info,
    Warning,
    Error
}

export type Refresh = {
    mode: RefreshMode;
    timeBetweenAutomaticRefreshes: number;
    maximumConsecutiveRefreshes: number;
}

export class GlobalSettings {
    static logEnabled: boolean = true;
    static logLevel: LogLevel = LogLevel.Error;
    static maximumRetryAttempts: number = 3;
    static defaultTimeBetweenRetryAttempts: number = 3000; // 3 seconds
    static authPromptWidth: number = 400;
    static authPromptHeight: number = 600;
    static allowTemplates: boolean = false;
    static readonly refresh: Refresh = {
        mode: RefreshMode.Manual,
        timeBetweenAutomaticRefreshes: 3000, // 3 seconds
        maximumConsecutiveRefreshes: 3
    };

    static onLogEvent?: (level: LogLevel, message?: any, ...optionalParams: any[]) => void;
}

export class ExecuteAction extends Adaptive.SubmitAction {
    //#region Schema

    static readonly verbProperty = new Adaptive.StringProperty(Adaptive.Versions.v1_2, "verb");

    @Adaptive.property(ExecuteAction.verbProperty)
    verb: string;

    //#endregion

    getJsonTypeName(): string {
        return "Action.Execute";
    }
}

export class RefreshActionProperty extends Adaptive.PropertyDefinition {
    parse(sender: RefreshDefinition, source: Adaptive.PropertyBag, context: Adaptive.SerializationContext): ExecuteAction | undefined {
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
                Adaptive.ValidationEvent.ActionTypeNotAllowed,
                "The \"refresh\" property must have its \"action\" field defined set to an Action.Execute object",
                sender);

            return undefined;
        }
    }

    toJSON(sender: Adaptive.SerializableObject, target: Adaptive.PropertyBag, value: ExecuteAction | undefined, context: Adaptive.SerializationContext) {
        context.serializeValue(target, this.name, value ? value.toJSON(context) : undefined);
    }

    constructor(readonly targetVersion: Adaptive.Version, readonly name: string) {
        super(targetVersion, name, undefined);
    }
}

export class RefreshDefinition extends Adaptive.SerializableObject {
    //#region Schema

    static readonly actionProperty = new RefreshActionProperty(Adaptive.Versions.v1_0, "action");

    @Adaptive.property(RefreshDefinition.actionProperty)
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

    parent: Adaptive.CardElement;
}

export class AdaptiveAppletCard extends Adaptive.AdaptiveCard {
    //#region Schema

    static readonly refreshProperty = new Adaptive.SerializableObjectProperty(Adaptive.Versions.v1_0, "refresh", RefreshDefinition, true);

    @Adaptive.property(AdaptiveAppletCard.refreshProperty)
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
    private static _elementsRegistry = new Adaptive.CardObjectRegistry<Adaptive.CardElement>();
    private static _actionsRegistry = new Adaptive.CardObjectRegistry<Adaptive.Action>();

    static initialize() {
        Adaptive.GlobalRegistry.populateWithDefaultElements(AdaptiveApplet._elementsRegistry);
        Adaptive.GlobalRegistry.populateWithDefaultActions(AdaptiveApplet._actionsRegistry);

        AdaptiveApplet._actionsRegistry.unregister("Action.Submit");
        AdaptiveApplet._actionsRegistry.register("Action.Execute", ExecuteAction, Adaptive.Versions.v1_2);
    }

    private _card?: AdaptiveAppletCard;
    private _cardPayload: any;
    private _cardData: any;
    private _allowAutomaticCardUpdate: boolean = false;
    private _refreshButtonHostElement: HTMLElement;
    private _cardHostElement: HTMLElement;

    private displayCard(card: Adaptive.AdaptiveCard) {
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
            
            if (GlobalSettings.refresh.mode === RefreshMode.Automatic) {
                let autoRefreshPausedMessage = Strings.refresh.automaticRefreshPaused;

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
                                    text: Strings.refresh.clckToRestartAutomaticRefresh,
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
                                    text: Strings.refresh.refreshThisCard,
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

            let card = new Adaptive.AdaptiveCard();
            card.parse(cardPayload, new Adaptive.SerializationContext(Adaptive.Versions.v1_2));
            card.onExecuteAction = (action: Adaptive.Action) => {
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
                consecutiveRefreshes: consecutiveRefreshes
            };

            let cancel = this.onPrepareActivityRequest ? !this.onPrepareActivityRequest(this, action, request) : false;

            return cancel ? undefined : request;
        }
        else {
            throw new Error("createActivityRequest: no card has been set.");
        }
    }

    private createMagicCodeInputCard(attemptNumber: number): Adaptive.AdaptiveCard {
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

        let card = new Adaptive.AdaptiveCard();
        card.parse(payload);

        return card;
    }

    private cancelAutomaticRefresh() {
        if (this._allowAutomaticCardUpdate) {
            logEvent(LogLevel.Warning, "Automatic card refresh has been cancelled as a result of the user interacting with the card.");
        }

        this._allowAutomaticCardUpdate = false;
    }

    private internalSetCard(payload: any, consecutiveRefreshes: number) {
        if (typeof payload === "object") {
            if (payload["type"] === "AdaptiveCard") {
                if (payload["$data"] !== undefined) {
                    this._cardData = payload["$data"];
                    delete payload["$data"];
                }

                this._cardPayload = payload;
            }
            else {
                this._cardData = payload;
            }
        }

        if (this._cardPayload) {
            try {
                let card = new AdaptiveAppletCard();

                let serializationContext = new Adaptive.SerializationContext();
                serializationContext.setElementRegistry(AdaptiveApplet._elementsRegistry);
                serializationContext.setActionRegistry(AdaptiveApplet._actionsRegistry);

                if (this._cardData && GlobalSettings.allowTemplates) {
                    let template = new Templating.Template(this._cardPayload);
                    let expandedCardPayload = template.expand(
                        {
                            $root: this._cardData
                        }
                    );

                    card.parse(expandedCardPayload, serializationContext);
                }
                else {
                    card.parse(this._cardPayload, serializationContext);
                }

                let doChangeCard = this.onCardChanging ? this.onCardChanging(this, this._cardPayload) : true;

                if (doChangeCard) {
                    this._card = card;
                    this._card.onExecuteAction = (action: Adaptive.Action) => {
                        // If the user takes an action, cancel any pending automatic refresh
                        this.cancelAutomaticRefresh();

                        this.internalExecuteAction(action, ActivityInvocationTrigger.Manual, 0);
                    }
                    this._card.onInputValueChanged = (input: Adaptive.Input) => {
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
                            if (GlobalSettings.refresh.mode === RefreshMode.Automatic && consecutiveRefreshes < GlobalSettings.refresh.maximumConsecutiveRefreshes) {
                                if (GlobalSettings.refresh.timeBetweenAutomaticRefreshes <= 0) {
                                    logEvent(LogLevel.Info, "Triggering automatic card refresh number " + (consecutiveRefreshes + 1));

                                    this.internalExecuteAction(this._card.refresh.action, ActivityInvocationTrigger.Automatic, consecutiveRefreshes + 1);
                                }
                                else {
                                    logEvent(LogLevel.Info, "Scheduling automatic card refresh number " + (consecutiveRefreshes + 1) + " in " + GlobalSettings.refresh.timeBetweenAutomaticRefreshes + "ms");

                                    let action = this._card.refresh.action;

                                    this._allowAutomaticCardUpdate = true;

                                    window.setTimeout(
                                        () => {
                                            if (this._allowAutomaticCardUpdate) {
                                                this.internalExecuteAction(action, ActivityInvocationTrigger.Automatic, consecutiveRefreshes + 1);
                                            }
                                        },
                                        GlobalSettings.refresh.timeBetweenAutomaticRefreshes
                                    )
                                }
                            }
                            else if (GlobalSettings.refresh.mode !== RefreshMode.Disabled) {
                                if (consecutiveRefreshes > 0) {
                                    logEvent(LogLevel.Warning, "Stopping automatic refreshes after " + consecutiveRefreshes + " consecutive refreshes. Showing a manual refresh button instead.");
                                }
                                else {
                                    logEvent(LogLevel.Warning, "The card has a refresh section, but automatic refreshes are disabled. Showing manual refresh button instead.");
                                }

                                this.displayRefreshButton(this._card.refresh.action);
                            }
                        }
                    }
                }
            }
            catch (error) {
                // Ignore all errors
                logEvent(LogLevel.Error, "setCard: " + error);
            }
        }
    }

    private internalExecuteAction(action: Adaptive.Action, trigger: ActivityInvocationTrigger, consecutiveRefreshes: number) {
        if (this.channelAdapter) {
            if (action instanceof ExecuteAction) {
                let request = this.createActivityRequest(action, trigger, consecutiveRefreshes);

                if (request) {
                    this.internalSendActivityRequestAsync(request);
                }
            }
            else {
                throw new Error("internalExecuteAction: Unsupported action type.");
            }
        }
        else {
            throw new Error("internalExecuteAction: No channel adapter set.");
        }
    }

    private activityRequestSucceeded(response: ActivityResponse) {
        if (this.onActivityRequestSucceeded) {
            this.onActivityRequestSucceeded(this, response);
        }
    }

    private activityRequestFailed(response: ActivityResponse): number {
        return this.onActivityRequestFailed ? this.onActivityRequestFailed(this, response) : GlobalSettings.defaultTimeBetweenRetryAttempts;
    }

    private async internalSendActivityRequestAsync(request: ActivityRequest) {
        if (!this.channelAdapter) {
            throw new Error("internalSendActivityRequestAsync: channelAdapter is not set.")
        }

        let overlay = this.createProgressOverlay(request.activity.value.trigger);

        this.renderedElement.appendChild(overlay);

        let done = false;

        while (!done) {
            let response: ActivityResponse | undefined = undefined;

            if (request.attemptNumber === 0) {
                logEvent(LogLevel.Info, "Sending activity request to channel (attempt " + (request.attemptNumber + 1) + ")");
            }
            else {
                logEvent(LogLevel.Info, "Re-sending activity request to channel (attempt " + (request.attemptNumber + 1) + ")");
            }

            try {
                response = await this.channelAdapter.sendRequestAsync(request);
            }
            catch (error) {
                logEvent(LogLevel.Error, "Activity request failed: " + error);

                this.renderedElement.removeChild(overlay);

                done = true;
            }

            if (response) {
                switch (response.status) {
                    case ActivityStatus.Success:
                        this.renderedElement.removeChild(overlay);

                        try {
                            response.content = JSON.parse(response.content);
                        }
                        catch {
                            // Leave the content as is
                        }

                        if (typeof response.content === "string") {
                            logEvent(LogLevel.Info, "The activity request returned a string after " + (request.attemptNumber + 1) + " attempt(s).");
                        }
                        else if (typeof response.content === "object") {
                            switch (response.content["type"]) {
                                case "AdaptiveCard":
                                    logEvent(LogLevel.Info, "The activity request returned an Adaptive Card after " + (request.attemptNumber + 1) + " attempt(s).");

                                    this.internalSetCard(response.content, request.consecutiveRefreshes);

                                    break;
                                case "Activity.InvocationError.Unauthorized":
                                    logEvent(LogLevel.Info, "The activity request returned Activity.InvocationError.Unauthorized after " + (request.attemptNumber + 1) + " attempt(s).");

                                    if ((request.attemptNumber + 1) <= GlobalSettings.maximumRetryAttempts) {
                                        let loginUrl: URL;

                                        try {
                                            loginUrl = new URL(response.content["loginUrl"]);
                                        }
                                        catch (e) {
                                            logEvent(LogLevel.Error, "Invalid loginUrl: " + response.content["loginUrl"]);

                                            throw e;
                                        }

                                        logEvent(LogLevel.Info, "Login required at " + loginUrl.toString());

                                        let magicCodeInputCard = this.createMagicCodeInputCard(request.attemptNumber);
                                        magicCodeInputCard.render();
                                        magicCodeInputCard.onExecuteAction = (submitMagicCodeAction: Adaptive.Action) => {
                                            if (this.card && submitMagicCodeAction instanceof Adaptive.SubmitAction) {
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
                                                        logEvent(LogLevel.Warning, "Authentication cancelled by user.");

                                                        this.displayCard(this.card);

                                                        break;
                                                    default:
                                                        logEvent(LogLevel.Error, "Unespected action taken from magic code input card (id = " + submitMagicCodeAction.id + ")");

                                                        alert("Something went wrong. This action can't be handled.");

                                                        break;
                                                }
                                            }
                                        }

                                        this.displayCard(magicCodeInputCard);

                                        let left = window.screenX + (window.outerWidth - GlobalSettings.authPromptWidth) / 2;
                                        let top = window.screenY + (window.outerHeight - GlobalSettings.authPromptHeight) / 2;

                                        window.open(loginUrl.toString(), "Login", `width=${GlobalSettings.authPromptWidth},height=${GlobalSettings.authPromptHeight},left=${left},top=${top}`);
                                    }
                                    else {
                                        logEvent(LogLevel.Error, "Authentication failed. Giving up after " + (request.attemptNumber + 1) + " attempt(s)");

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

                        if (retryIn >= 0 && (request.attemptNumber + 1) < GlobalSettings.maximumRetryAttempts) {
                            logEvent(LogLevel.Warning, "Activity request failed. Retrying in " + retryIn + "ms");

                            request.attemptNumber++;

                            await new Promise(
                                (resolve, reject) => {
                                    window.setTimeout(
                                        () => { resolve(); },
                                        retryIn
                                    )
                                });
                        }
                        else {
                            logEvent(LogLevel.Error, "Activity request failed. Giving up after " + (request.attemptNumber + 1) + " attempt(s)");

                            this.renderedElement.removeChild(overlay);

                            done = true;
                        }

                        break;
                }
            }
        }
    }

    private createProgressOverlay(trigger: ActivityInvocationTrigger): HTMLElement {
        let overlay: HTMLElement | undefined = undefined;

        if (this.onCreateProgressOverlay) {
            overlay = this.onCreateProgressOverlay(this, trigger);
        }

        if (!overlay) {
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
    channelAdapter: ChannelAdapter | undefined = undefined;

    onCardChanging?: (sender: AdaptiveApplet, card: any) => boolean;
    onCardChanged?: (sender: AdaptiveApplet) => void;
    onPrepareActivityRequest?: (sender: AdaptiveApplet, action: ExecuteAction, request: ActivityRequest) => boolean;
    onActivityRequestSucceeded?: (sender: AdaptiveApplet, response: ActivityResponse) => void;
    onActivityRequestFailed?: (sender: AdaptiveApplet, response: ActivityResponse) => number;
    onCreateProgressOverlay?: (sender: AdaptiveApplet, actionExecutionTrigger: ActivityInvocationTrigger) => HTMLElement | undefined;
    onRenderRefreshButton?: (sender: AdaptiveApplet) => HTMLElement | undefined;

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
