import * as Adaptive from "adaptivecards";
import * as Templating from "adaptivecards-templating";
import { ChannelAdapter } from "./channel-adapter";
import { ActivityStatus, ActivityResponse, ActivityRequest, ActivityInvocationContext } from "./invoke-activity";

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

export class AutoRefreshActionProperty extends Adaptive.PropertyDefinition {
    parse(sender: AutoRefreshDefinition, source: Adaptive.PropertyBag, context: Adaptive.SerializationContext): ExecuteAction | undefined {
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
                "\"autoRefresh\" must have its \"action\" property defined as an Action.Execute object",
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

export class AutoRefreshDefinition extends Adaptive.SerializableObject {
    //#region Schema

    static readonly userIdsProperty = new Adaptive.StringArrayProperty(Adaptive.Versions.v1_0, "userIds");
    static readonly displayCurrentCardWhileRefreshingProperty = new Adaptive.BoolProperty(Adaptive.Versions.v1_0, "displayCurrentCardWhileRefreshing", true);
    static readonly actionProperty = new AutoRefreshActionProperty(Adaptive.Versions.v1_0, "action");

    @Adaptive.property(AutoRefreshDefinition.userIdsProperty)
    userIds: string[];

    @Adaptive.property(AutoRefreshDefinition.displayCurrentCardWhileRefreshingProperty)
    displayCurrentCardWhileRefreshing: boolean;

    @Adaptive.property(AutoRefreshDefinition.actionProperty)
    get action(): ExecuteAction {
        return this.getValue(AutoRefreshDefinition.actionProperty);
    }

    set action(value: ExecuteAction) {
        this.setValue(AutoRefreshDefinition.actionProperty, value);

        if (value) {
            value.setParent(this.parent);
        }
    }

    protected getSchemaKey(): string {
        return "AutoRefreshDefinition";
    }

    //#endregion

    parent: Adaptive.CardElement;
}

export class AdaptiveAppletCard extends Adaptive.AdaptiveCard {
    //#region Schema

    static readonly appIdProperty = new Adaptive.StringProperty(Adaptive.Versions.v1_0, "appId", true);
    static readonly autoRefreshProperty = new Adaptive.SerializableObjectProperty(Adaptive.Versions.v1_0, "autoRefresh", AutoRefreshDefinition, true);

    @Adaptive.property(AdaptiveAppletCard.appIdProperty)
    appId: string;

    @Adaptive.property(AdaptiveAppletCard.autoRefreshProperty)
    get autoRefresh(): AutoRefreshDefinition | undefined {
        return this.getValue(AdaptiveAppletCard.autoRefreshProperty);
    }

    set autoRefresh(value: AutoRefreshDefinition | undefined) {
        this.setValue(AdaptiveAppletCard.autoRefreshProperty, value);

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

    static maximumRequestAttempts: number = 3;
    static defaultTimeBetweenAttempts: number = 3000; // 3 seconds
    static authPromptWidth: number = 400;
    static authPromptHeight: number = 600;

    static initialize() {
        Adaptive.GlobalRegistry.populateWithDefaultElements(AdaptiveApplet._elementsRegistry);
        Adaptive.GlobalRegistry.populateWithDefaultActions(AdaptiveApplet._actionsRegistry);

        AdaptiveApplet._actionsRegistry.unregister("Action.Submit");
        AdaptiveApplet._actionsRegistry.register("Action.Execute", ExecuteAction, Adaptive.Versions.v1_2);
    }

    private _card?: AdaptiveAppletCard;
    private _cardPayload: any;
    private _cardData: any;

    private displayCard(card: Adaptive.AdaptiveCard) {
        if (card.renderedElement) {
            while (this.renderedElement.firstChild) {
                this.renderedElement.removeChild(this.renderedElement.firstChild);
            }

            this.renderedElement.appendChild(card.renderedElement);
        }
        else {
            throw new Error("displayCard: undefined card.");
        }
    }

    private createActivityRequest(action: ExecuteAction, context: ActivityInvocationContext): ActivityRequest | undefined {
        if (this.card) {
            let request: ActivityRequest = {
                context: context,
                activity: {
                    type: "invoke",
                    name: "adaptiveCard/action",
                    appId: this.card.appId,
                    localTimezone: "",
                    localTimestamp: "",
                    value: {
                        action: {
                            type: "Action.Execute",
                            id: action.id,
                            verb: action.verb,
                            data: action.data
                        }
                    }
                },
                attemptNumber: 0
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

    private internalExecuteAction(action: Adaptive.Action, context: ActivityInvocationContext) {
        if (this.channelAdapter) {
            if (action instanceof ExecuteAction) {
                let request = this.createActivityRequest(action, context);

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

    private async internalSendActivityRequestAsync(request: ActivityRequest) {
        if (!this.channelAdapter) {
            throw new Error("internalSendActivityRequestAsync: channelAdapter is not set.")
        }

        let overlay = this.createProgressOverlay(request.context);

        this.renderedElement.appendChild(overlay);

        let done = false;

        while (!done) {
            let response: ActivityResponse | undefined = undefined;

            if (request.attemptNumber === 0) {
                console.log("Sending activity request to channel (attempt " + (request.attemptNumber + 1) + ")");
            }
            else {
                console.log("Re-sending activity request to channel (attempt " + (request.attemptNumber + 1) + ")");
            }

            try {
                response = await this.channelAdapter.sendRequestAsync(request);
            }
            catch (error) {
                console.error("Activity request failed: " + error);

                this.renderedElement.removeChild(overlay);
                
                done = true;

                alert("Something went wrong: " + error);
            }

            if (response) {
                switch (response.status) {
                    case ActivityStatus.Success:
                        this.renderedElement.removeChild(overlay);
                
                        let parsedResult: any = undefined;

                        try {
                            parsedResult = JSON.parse(response.content);
                        }
                        catch {
                            parsedResult = response.content;
                        }

                        if (typeof parsedResult === "string") {
                            console.log("The activity request returned a string after " + (request.attemptNumber + 1) + " attempt(s).");

                            alert(parsedResult);
                        }
                        else if (typeof parsedResult === "object") {
                            switch (parsedResult["type"]) {
                                case "AdaptiveCard":
                                    console.log("The activity request returned an Adaptive Card after " + (request.attemptNumber + 1) + " attempt(s).");

                                    this.setCard(parsedResult);

                                    break;
                                case "Activity.InvocationError.Unauthorized":
                                    console.log("The activity request returned Activity.InvocationError.Unauthorized after " + (request.attemptNumber + 1) + " attempt(s).");

                                    if ((request.attemptNumber + 1) <= AdaptiveApplet.maximumRequestAttempts) {
                                        let loginUrl: URL;

                                        try {
                                            loginUrl = new URL(parsedResult["loginUrl"]);
                                        }
                                        catch (e) {
                                            console.error("Invalid loginUrl: " + parsedResult["loginUrl"]);

                                            throw e;
                                        }

                                        console.log("Login required at " + loginUrl.toString());

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
                                                        console.warn("Authentication cancelled by user.");

                                                        this.displayCard(this.card);

                                                        break;
                                                    default:
                                                        console.error("Unespected action taken from magic code input card (id = " + submitMagicCodeAction.id + ")");

                                                        alert("Something went wrong. This action can't be handled.");

                                                        break;
                                                }
                                            }
                                        }

                                        this.displayCard(magicCodeInputCard);

                                        let left = window.screenX + (window.outerWidth - AdaptiveApplet.authPromptWidth) / 2;
                                        let top = window.screenY + (window.outerHeight - AdaptiveApplet.authPromptHeight) / 2;

                                        window.open(loginUrl.toString(), "Login", `width=${AdaptiveApplet.authPromptWidth},height=${AdaptiveApplet.authPromptHeight},left=${left},top=${top}`);
                                    }
                                    else {
                                        console.error("Authentication failed. Giving up after " + (request.attemptNumber + 1) + " attempt(s)");

                                        alert("Authentication failed.");
                                    }

                                    break;
                                default:
                                    throw new Error("internalSendActivityRequestAsync: Action.Execute result is of unsupported type (" + typeof parsedResult + ")");
                            }                                    
                        }
                        else {
                            throw new Error("internalSendActivityRequestAsync: Action.Execute result is of unsupported type (" + typeof parsedResult + ")");
                        }

                        done = true;

                        break;
                    case ActivityStatus.Failure:
                    default:
                        let retryIn: number = this.onActivityRequestCompleted ? this.onActivityRequestCompleted(this, response) : AdaptiveApplet.defaultTimeBetweenAttempts;

                        if (retryIn >= 0 && (request.attemptNumber + 1) < AdaptiveApplet.maximumRequestAttempts) {
                            console.warn("Activity request failed. Retrying in " + retryIn + "ms");

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
                            console.error("Activity request failed. Giving up after " + (request.attemptNumber + 1) + " attempt(s)");

                            this.renderedElement.removeChild(overlay);

                            done = true;

                            alert(response.content);
                        }

                        break;
                }
            }
        }
    }

    private createProgressOverlay(context: ActivityInvocationContext): HTMLElement {
        let overlay: HTMLElement | undefined = undefined;

        if (this.onCreateProgressOverlay) {
            overlay = this.onCreateProgressOverlay(this, context);
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
    onActivityRequestCompleted?: (sender: AdaptiveApplet, response: ActivityResponse) => number;
    onCreateProgressOverlay?: (sender: AdaptiveApplet, actionExecutionContext: ActivityInvocationContext) => HTMLElement | undefined;

    constructor() {
        this.renderedElement = document.createElement("div");
        this.renderedElement.style.position = "relative";
    }

    setCard(payload: any) {
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

                if (this._cardData) {
                    let evaluationContext = new Templating.EvaluationContext();
                    evaluationContext.$root = this._cardData;

                    let template = new Templating.Template(this._cardPayload)
                    let expandedCardPayload = template.expand(evaluationContext);

                    card.parse(expandedCardPayload, serializationContext);
                }
                else {
                    card.parse(this._cardPayload, serializationContext);
                }

                if (!card.appId) {
                    throw new Error("Invalid card payload. The appId property is missing.")
                }

                let doChangeCard = this.onCardChanging ? this.onCardChanging(this, this._cardPayload) : true;

                if (doChangeCard) {
                    this._card = card;
                    this._card.onExecuteAction = (action: Adaptive.Action) => {
                        this.internalExecuteAction(action, ActivityInvocationContext.UserInteraction);
                    }

                    this._card.render();

                    if (this._card.renderedElement) {
                        this.displayCard(this._card);

                        if (this.onCardChanged) {
                            this.onCardChanged(this);
                        }

                        if (this._card.autoRefresh) {
                            this.internalExecuteAction(this._card.autoRefresh.action, ActivityInvocationContext.AutoRefresh);
                        }
                    }
                }
            }
            catch (error) {
                // Ignore all errors
                console.error("setCard: " + error);
            }
        }
    }

    get card(): AdaptiveAppletCard | undefined {
        return this._card;
    }
}

AdaptiveApplet.initialize();