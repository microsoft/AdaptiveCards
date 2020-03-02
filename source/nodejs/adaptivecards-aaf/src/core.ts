import * as Adaptive from "adaptivecards";
import * as Templating from "adaptivecards-templating";
import { ChannelAdapter } from "./channel-adapter";
import { ActivityStatus, ActivityResponse, ActivityRequest } from "./invoke-activity";
import { CardElement } from "adaptivecards";

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

    parent: CardElement;
}

export class AdaptiveAppletCard extends Adaptive.AdaptiveCard {
    //#region Schema

    static readonly autoRefreshProperty = new Adaptive.SerializableObjectProperty(Adaptive.Versions.v1_0, "autoRefresh", AutoRefreshDefinition, true);

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
    static maximumRequestAttempts: number = 3;
    static defaultTimeBetweenAttempts: number = 3000; // 3 seconds

    private _card: AdaptiveAppletCard | undefined;
    private _cardPayload: any;
    private _cardData: any;

    private createActivityRequest(action: ExecuteAction): ActivityRequest | undefined {
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
                    }
                }
            },
            attemptNumber: 0
        };

        let cancel = this.onPrepareActivityRequest ? !this.onPrepareActivityRequest(this, action, request) : false;

        return cancel ? undefined : request;
    }

    private async internalExecuteActionAsync(action: Adaptive.Action) {
        if (action instanceof ExecuteAction && this.channelAdapter) {
            let request = this.createActivityRequest(action);

            if (request) {
                let overlay = this.createOverlay();

                this.renderedElement.appendChild(overlay);

                let done = false;

                while (!done) {
                    let response: ActivityResponse | undefined = undefined;

                    console.log("Sending activity request to channel (attempt " + (request.attemptNumber + 1) + ")");

                    try {
                        response = await this.channelAdapter.sendRequestAsync(request);
                    }
                    catch (error) {
                        console.log("Activity request failed: " + error);

                        this.renderedElement.removeChild(overlay);

                        done = true;

                        alert("Something went wrong: " + error);
                    }

                    if (response) {
                        switch (response.status) {
                            case ActivityStatus.Success:
                                console.log("Activity request succeeded in " + (request.attemptNumber + 1) + " attempt(s)");

                                this.renderedElement.removeChild(overlay);

                                let parsedResult: any = undefined;

                                try {
                                    parsedResult = JSON.parse(response.content);
                                }
                                catch {
                                    parsedResult = response.content;
                                }

                                if (typeof parsedResult === "string") {
                                    alert(parsedResult);
                                }
                                else if (typeof parsedResult === "object") {
                                    this.setCard(parsedResult);
                                }
                                else {
                                    throw new Error("Action.Execute result is of unsupported type (" + typeof parsedResult + ")");
                                }

                                done = true;

                                break;
                            case ActivityStatus.Failure:
                            default:
                                let retryIn: number = this.onActivityRequestCompleted ? this.onActivityRequestCompleted(this, response) : AdaptiveApplet.defaultTimeBetweenAttempts;

                                if (retryIn >= 0 && (request.attemptNumber + 1) < AdaptiveApplet.maximumRequestAttempts) {
                                    console.log("Activity request failed. Retrying in " + retryIn + "ms");

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
                                    console.log("Activity request failed. Giving up after " + (request.attemptNumber + 1) + " attempt(s)");

                                    this.renderedElement.removeChild(overlay);

                                    done = true;

                                    alert(response.content);
                                }

                                break;
                        }
                    }
                }
            }
        }
        else {
            throw new Error("No channel adapter set.");
        }
    }

    private createOverlay(): HTMLElement {
        let overlay = document.createElement("div");
        overlay.style.position = "absolute";
        overlay.style.left = "0";
        overlay.style.top = "0";
        overlay.style.width = "100%";
        overlay.style.height = "100%";
        overlay.style.backgroundColor = "rgba(255, 0, 0, 0.5)";

        return overlay;
    }

    readonly renderedElement: HTMLElement;

    userId?: string;
    channelAdapter: ChannelAdapter | undefined = undefined;

    onCardChanging?: (sender: AdaptiveApplet, card: any) => boolean;
    onCardChanged?: (sender: AdaptiveApplet) => void;
    onPrepareActivityRequest?: (sender: AdaptiveApplet, action: ExecuteAction, request: ActivityRequest) => boolean;
    onActivityRequestCompleted?: (sender: AdaptiveApplet, response: ActivityResponse) => number;

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

                if (this._cardData) {
                    let evaluationContext = new Templating.EvaluationContext();
                    evaluationContext.$root = this._cardData;

                    let template = new Templating.Template(this._cardPayload)
                    let expandedCardPayload = template.expand(evaluationContext);

                    card.parse(expandedCardPayload);
                }
                else {
                    card.parse(this._cardPayload);
                }

                let doChangeCard = this.onCardChanging ? this.onCardChanging(this, this._cardPayload) : true;

                if (doChangeCard) {
                    this._card = card;
                    this._card.onExecuteAction = (action: Adaptive.Action) => {
                        this.internalExecuteActionAsync(action);
                    }

                    while (this.renderedElement.firstChild) {
                        this.renderedElement.removeChild(this.renderedElement.firstChild);
                    }

                    this._card.render();

                    if (this._card.renderedElement) {
                        this.renderedElement.appendChild(this._card.renderedElement)

                        if (this.onCardChanged) {
                            this.onCardChanged(this);
                        }

                        if (this._card.autoRefresh) {
                            this.internalExecuteActionAsync(this._card.autoRefresh.action);
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

function initialize() {
    Adaptive.GlobalRegistry.actions.unregister("Action.Submit");
    Adaptive.GlobalRegistry.actions.register("Action.Execute", ExecuteAction, Adaptive.Versions.v1_2);
}

initialize();
