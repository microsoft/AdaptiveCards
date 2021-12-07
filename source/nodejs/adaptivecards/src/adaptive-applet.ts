// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";
import * as Utils from "./utils";
import { GlobalSettings } from "./shared";
import { ChannelAdapter } from "./channel-adapter";
import {
    ActivityResponse,
    IActivityRequest,
    ActivityRequestTrigger,
    SuccessResponse,
    ErrorResponse,
    LoginRequestResponse
} from "./activity-request";
import { Strings } from "./strings";
import {
    SubmitAction,
    ExecuteAction,
    SerializationContext,
    AdaptiveCard,
    Action,
    Input,
    TokenExchangeResource,
    AuthCardButton
} from "./card-elements";
import { Versions } from "./serialization";
import { HostConfig } from "./host-config";

function logEvent(level: Enums.LogLevel, message?: any, ...optionalParams: any[]) {
    if (GlobalSettings.applets.logEnabled) {
        if (GlobalSettings.applets.onLogEvent) {
            GlobalSettings.applets.onLogEvent(level, message, optionalParams);
        } else {
            /* eslint-disable no-console */
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
            /* eslint-enable no-console */
        }
    }
}

class ActivityRequest implements IActivityRequest {
    constructor(
        readonly action: ExecuteAction,
        readonly trigger: ActivityRequestTrigger,
        readonly consecutiveRefreshes: number
    ) {}

    authCode?: string;
    authToken?: string;
    attemptNumber: number = 0;

    onSend: (sender: ActivityRequest) => void;

    // eslint-disable-next-line @typescript-eslint/require-await
    async retryAsync(): Promise<void> {
        if (this.onSend) {
            this.onSend(this);
        }
    }
}

export class AdaptiveApplet {
    private static readonly _submitMagicCodeActionId = "submitMagicCode";
    private static readonly _cancelMagicCodeAuthActionId = "cancelMagicCodeAuth";

    private _card?: AdaptiveCard;
    private _cardPayload: any;
    private _allowAutomaticCardUpdate: boolean = false;
    private _refreshButtonHostElement: HTMLElement;
    private _cardHostElement: HTMLElement;
    private _progressOverlay?: HTMLElement;

    private displayCard(card: AdaptiveCard) {
        if (card.renderedElement) {
            Utils.clearElementChildren(this._cardHostElement);

            this._refreshButtonHostElement.style.display = "none";

            this._cardHostElement.appendChild(card.renderedElement);
        } else {
            throw new Error("displayCard: undefined card.");
        }
    }

    private showManualRefreshButton(refreshAction: ExecuteAction) {
        const displayBuiltInManualRefreshButton = this.onShowManualRefreshButton
            ? this.onShowManualRefreshButton(this)
            : true;

        if (displayBuiltInManualRefreshButton) {
            this._refreshButtonHostElement.style.display = "none";

            let renderedRefreshButton: HTMLElement | undefined = undefined;

            if (this.onRenderManualRefreshButton) {
                renderedRefreshButton = this.onRenderManualRefreshButton(this);
            } else {
                let message = Strings.runtime.refreshThisCard();

                if (GlobalSettings.applets.refresh.mode === Enums.RefreshMode.Automatic) {
                    let autoRefreshPausedMessage = Strings.runtime.automaticRefreshPaused();

                    if (autoRefreshPausedMessage[autoRefreshPausedMessage.length - 1] !== " ") {
                        autoRefreshPausedMessage += " ";
                    }

                    message = Strings.runtime.clckToRestartAutomaticRefresh();
                }

                const cardPayload = {
                    type: "AdaptiveCard",
                    version: "1.2",
                    body: [
                        {
                            type: "RichTextBlock",
                            horizontalAlignment: "right",
                            inlines: [
                                {
                                    type: "TextRun",
                                    text: message,
                                    selectAction: {
                                        type: "Action.Submit",
                                        id: "refreshCard"
                                    }
                                }
                            ]
                        }
                    ]
                };

                const card = new AdaptiveCard();
                card.parse(cardPayload, new SerializationContext(Versions.v1_2));
                card.onExecuteAction = (action: Action) => {
                    if (action.id === "refreshCard") {
                        Utils.clearElementChildren(this._refreshButtonHostElement);

                        this.internalExecuteAction(
                            refreshAction,
                            ActivityRequestTrigger.Automatic,
                            0
                        );
                    }
                };

                renderedRefreshButton = card.render();
            }

            if (renderedRefreshButton) {
                Utils.clearElementChildren(this._refreshButtonHostElement);

                this._refreshButtonHostElement.appendChild(renderedRefreshButton);

                this._refreshButtonHostElement.style.removeProperty("display");
            }
        }
    }

    private createActivityRequest(
        action: ExecuteAction,
        trigger: ActivityRequestTrigger,
        consecutiveRefreshes: number
    ): ActivityRequest | undefined {
        if (this.card) {
            const request = new ActivityRequest(action, trigger, consecutiveRefreshes);
            request.onSend = (sender: ActivityRequest) => {
                sender.attemptNumber++;

                void this.internalSendActivityRequestAsync(request);
            };

            const cancel = this.onPrepareActivityRequest
                ? !this.onPrepareActivityRequest(this, request, action)
                : false;

            return cancel ? undefined : request;
        } else {
            throw new Error("createActivityRequest: no card has been set.");
        }
    }

    private createMagicCodeInputCard(attemptNumber: number): AdaptiveCard {
        const payload = {
            type: "AdaptiveCard",
            version: "1.0",
            body: [
                {
                    type: "TextBlock",
                    color: "attention",
                    text: attemptNumber === 1 ? undefined : "That didn't work... let's try again.",
                    wrap: true,
                    horizontalAlignment: "center"
                },
                {
                    type: "TextBlock",
                    text: 'Please login in the popup. You will obtain a magic code. Paste that code below and select "Submit"',
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
                            id: AdaptiveApplet._submitMagicCodeActionId,
                            title: "Submit"
                        },
                        {
                            type: "Action.Submit",
                            id: AdaptiveApplet._cancelMagicCodeAuthActionId,
                            title: "Cancel"
                        }
                    ]
                }
            ]
        };

        const card = new AdaptiveCard();
        card.parse(payload);

        return card;
    }

    private cancelAutomaticRefresh() {
        if (this._allowAutomaticCardUpdate) {
            logEvent(
                Enums.LogLevel.Warning,
                "Automatic card refresh has been cancelled as a result of the user interacting with the card."
            );
        }

        this._allowAutomaticCardUpdate = false;
    }

    private createSerializationContext(): SerializationContext {
        return this.onCreateSerializationContext
            ? this.onCreateSerializationContext(this)
            : new SerializationContext();
    }

    private internalSetCard(payload: any, consecutiveRefreshes: number) {
        if (typeof payload === "object" && payload["type"] === "AdaptiveCard") {
            this._cardPayload = payload;
        }

        if (this._cardPayload) {
            try {
                const card = new AdaptiveCard();

                if (this.hostConfig) {
                    card.hostConfig = this.hostConfig;
                }

                const serializationContext = this.createSerializationContext();

                card.parse(this._cardPayload, serializationContext);

                const doChangeCard = this.onCardChanging
                    ? this.onCardChanging(this, this._cardPayload)
                    : true;

                if (doChangeCard) {
                    this._card = card;

                    if (
                        this._card.authentication &&
                        this._card.authentication.tokenExchangeResource &&
                        this.onPrefetchSSOToken
                    ) {
                        this.onPrefetchSSOToken(
                            this,
                            this._card.authentication.tokenExchangeResource
                        );
                    }

                    this._card.onExecuteAction = (action: Action) => {
                        // If the user takes an action, cancel any pending automatic refresh
                        this.cancelAutomaticRefresh();

                        this.internalExecuteAction(action, ActivityRequestTrigger.Manual, 0);
                    };
                    this._card.onInputValueChanged = (_input: Input) => {
                        // If the user modifies an input, cancel any pending automatic refresh
                        this.cancelAutomaticRefresh();
                    };

                    this._card.render();

                    if (this._card.renderedElement) {
                        this.displayCard(this._card);

                        if (this.onCardChanged) {
                            this.onCardChanged(this);
                        }

                        if (this._card.refresh) {
                            if (
                                GlobalSettings.applets.refresh.mode ===
                                    Enums.RefreshMode.Automatic &&
                                consecutiveRefreshes <
                                    GlobalSettings.applets.refresh
                                        .maximumConsecutiveAutomaticRefreshes
                            ) {
                                if (
                                    GlobalSettings.applets.refresh.timeBetweenAutomaticRefreshes <=
                                    0
                                ) {
                                    logEvent(
                                        Enums.LogLevel.Info,
                                        "Triggering automatic card refresh number " +
                                            (consecutiveRefreshes + 1)
                                    );

                                    this.internalExecuteAction(
                                        this._card.refresh.action,
                                        ActivityRequestTrigger.Automatic,
                                        consecutiveRefreshes + 1
                                    );
                                } else {
                                    logEvent(
                                        Enums.LogLevel.Info,
                                        "Scheduling automatic card refresh number " +
                                            (consecutiveRefreshes + 1) +
                                            " in " +
                                            GlobalSettings.applets.refresh
                                                .timeBetweenAutomaticRefreshes +
                                            "ms"
                                    );

                                    const action = this._card.refresh.action;

                                    this._allowAutomaticCardUpdate = true;

                                    window.setTimeout(() => {
                                        if (this._allowAutomaticCardUpdate) {
                                            this.internalExecuteAction(
                                                action,
                                                ActivityRequestTrigger.Automatic,
                                                consecutiveRefreshes + 1
                                            );
                                        }
                                    }, GlobalSettings.applets.refresh.timeBetweenAutomaticRefreshes);
                                }
                            } else if (
                                GlobalSettings.applets.refresh.mode !== Enums.RefreshMode.Disabled
                            ) {
                                if (consecutiveRefreshes > 0) {
                                    logEvent(
                                        Enums.LogLevel.Warning,
                                        "Stopping automatic refreshes after " +
                                            consecutiveRefreshes +
                                            " consecutive refreshes."
                                    );
                                } else {
                                    logEvent(
                                        Enums.LogLevel.Warning,
                                        "The card has a refresh section, but automatic refreshes are disabled."
                                    );
                                }

                                if (
                                    GlobalSettings.applets.refresh
                                        .allowManualRefreshesAfterAutomaticRefreshes ||
                                    GlobalSettings.applets.refresh.mode === Enums.RefreshMode.Manual
                                ) {
                                    logEvent(Enums.LogLevel.Info, "Showing manual refresh button.");

                                    this.showManualRefreshButton(this._card.refresh.action);
                                }
                            }
                        }
                    }
                }
            } catch (error) {
                // Ignore all errors
                logEvent(Enums.LogLevel.Error, "setCard: " + error);
            }
        }
    }

    private internalExecuteAction(
        action: Action,
        trigger: ActivityRequestTrigger,
        consecutiveRefreshes: number
    ) {
        if (action instanceof ExecuteAction) {
            if (this.channelAdapter) {
                const request = this.createActivityRequest(action, trigger, consecutiveRefreshes);

                if (request) {
                    void request.retryAsync();
                }
            } else {
                throw new Error("internalExecuteAction: No channel adapter set.");
            }
        }

        if (this.onAction) {
            this.onAction(this, action);
        }
    }

    private createProgressOverlay(request: ActivityRequest): HTMLElement | undefined {
        if (!this._progressOverlay) {
            if (this.onCreateProgressOverlay) {
                this._progressOverlay = this.onCreateProgressOverlay(this, request);
            } else {
                this._progressOverlay = document.createElement("div");
                this._progressOverlay.className = "aaf-progress-overlay";

                const spinner = document.createElement("div");
                spinner.className = "aaf-spinner";
                spinner.style.width = "28px";
                spinner.style.height = "28px";

                this._progressOverlay.appendChild(spinner);
            }
        }

        return this._progressOverlay;
    }

    private removeProgressOverlay(request: IActivityRequest) {
        if (this.onRemoveProgressOverlay) {
            this.onRemoveProgressOverlay(this, request);
        }

        if (this._progressOverlay !== undefined) {
            this.renderedElement.removeChild(this._progressOverlay);

            this._progressOverlay = undefined;
        }
    }

    private activityRequestSucceeded(
        response: SuccessResponse,
        parsedContent: string | AdaptiveCard | undefined
    ) {
        if (this.onActivityRequestSucceeded) {
            this.onActivityRequestSucceeded(this, response, parsedContent);
        }
    }

    private activityRequestFailed(response: ErrorResponse): number {
        return this.onActivityRequestFailed
            ? this.onActivityRequestFailed(this, response)
            : GlobalSettings.applets.defaultTimeBetweenRetryAttempts;
    }

    private showAuthCodeInputDialog(request: ActivityRequest) {
        const showBuiltInAuthCodeInputCard = this.onShowAuthCodeInputDialog
            ? this.onShowAuthCodeInputDialog(this, request)
            : true;

        if (showBuiltInAuthCodeInputCard) {
            const authCodeInputCard = this.createMagicCodeInputCard(request.attemptNumber);
            authCodeInputCard.render();
            authCodeInputCard.onExecuteAction = (submitMagicCodeAction: Action) => {
                if (this.card && submitMagicCodeAction instanceof SubmitAction) {
                    switch (submitMagicCodeAction.id) {
                        case AdaptiveApplet._submitMagicCodeActionId:
                            let authCode: string | undefined = undefined;

                            if (
                                submitMagicCodeAction.data &&
                                typeof (<any>submitMagicCodeAction.data)["magicCode"] === "string"
                            ) {
                                authCode = (<any>submitMagicCodeAction.data)["magicCode"];
                            }

                            if (authCode) {
                                this.displayCard(this.card);

                                request.authCode = authCode;
                                void request.retryAsync();
                            } else {
                                alert("Please enter the magic code you received.");
                            }

                            break;
                        case AdaptiveApplet._cancelMagicCodeAuthActionId:
                            logEvent(Enums.LogLevel.Warning, "Authentication cancelled by user.");

                            this.displayCard(this.card);

                            break;
                        default:
                            logEvent(
                                Enums.LogLevel.Error,
                                "Unexpected action taken from magic code input card (id = " +
                                    submitMagicCodeAction.id +
                                    ")"
                            );

                            alert(Strings.magicCodeInputCard.somethingWentWrong());

                            break;
                    }
                }
            };

            this.displayCard(authCodeInputCard);
        }
    }

    private async internalSendActivityRequestAsync(request: ActivityRequest) {
        if (!this.channelAdapter) {
            throw new Error("internalSendActivityRequestAsync: channelAdapter is not set.");
        }

        const overlay = this.createProgressOverlay(request);

        if (overlay !== undefined) {
            this.renderedElement.appendChild(overlay);
        }

        let done = false;

        while (!done) {
            let response: ActivityResponse | undefined = undefined;

            if (request.attemptNumber === 1) {
                logEvent(
                    Enums.LogLevel.Info,
                    "Sending activity request to channel (attempt " + request.attemptNumber + ")"
                );
            } else {
                logEvent(
                    Enums.LogLevel.Info,
                    "Re-sending activity request to channel (attempt " + request.attemptNumber + ")"
                );
            }

            try {
                response = await this.channelAdapter.sendRequestAsync(request);
            } catch (error) {
                logEvent(Enums.LogLevel.Error, "Activity request failed: " + error);

                this.removeProgressOverlay(request);

                done = true;
            }

            if (response) {
                if (response instanceof SuccessResponse) {
                    this.removeProgressOverlay(request);

                    if (response.rawContent === undefined) {
                        throw new Error(
                            "internalSendActivityRequestAsync: Action.Execute result is undefined"
                        );
                    }

                    let parsedContent = response.rawContent;

                    try {
                        parsedContent = JSON.parse(response.rawContent);
                    } catch {
                        // Leave parseContent as is
                    }

                    if (typeof parsedContent === "string") {
                        logEvent(
                            Enums.LogLevel.Info,
                            "The activity request returned a string after " +
                                request.attemptNumber +
                                " attempt(s)."
                        );

                        this.activityRequestSucceeded(response, parsedContent);
                    } else if (
                        typeof parsedContent === "object" &&
                        parsedContent["type"] === "AdaptiveCard"
                    ) {
                        logEvent(
                            Enums.LogLevel.Info,
                            "The activity request returned an Adaptive Card after " +
                                request.attemptNumber +
                                " attempt(s)."
                        );

                        this.internalSetCard(parsedContent, request.consecutiveRefreshes);
                        this.activityRequestSucceeded(response, this.card);
                    } else {
                        throw new Error(
                            "internalSendActivityRequestAsync: Action.Execute result is of unsupported type (" +
                                typeof response.rawContent +
                                ")"
                        );
                    }

                    done = true;
                } else if (response instanceof ErrorResponse) {
                    const retryIn: number = this.activityRequestFailed(response);

                    if (
                        retryIn >= 0 &&
                        request.attemptNumber < GlobalSettings.applets.maximumRetryAttempts
                    ) {
                        logEvent(
                            Enums.LogLevel.Warning,
                            `Activity request failed: ${response.error.message}. Retrying in ${retryIn}ms`
                        );

                        request.attemptNumber++;

                        await new Promise<void>((resolve, _reject) => {
                            window.setTimeout(() => {
                                resolve();
                            }, retryIn);
                        });
                    } else {
                        logEvent(
                            Enums.LogLevel.Error,
                            `Activity request failed: ${response.error.message}. Giving up after ${request.attemptNumber} attempt(s)`
                        );

                        this.removeProgressOverlay(request);

                        done = true;
                    }
                } else if (response instanceof LoginRequestResponse) {
                    logEvent(
                        Enums.LogLevel.Info,
                        "The activity request returned a LoginRequestResponse after " +
                            request.attemptNumber +
                            " attempt(s)."
                    );

                    if (request.attemptNumber <= GlobalSettings.applets.maximumRetryAttempts) {
                        let attemptOAuth = true;

                        if (response.tokenExchangeResource && this.onSSOTokenNeeded) {
                            // Attempt to use SSO. The host will return true if it can handle SSO, in which case
                            // we bypass OAuth
                            attemptOAuth = !this.onSSOTokenNeeded(
                                this,
                                request,
                                response.tokenExchangeResource
                            );
                        }

                        if (attemptOAuth) {
                            // Attempt to use OAuth
                            this.removeProgressOverlay(request);

                            if (response.signinButton === undefined) {
                                throw new Error(
                                    "internalSendActivityRequestAsync: the login request doesn't contain a valid signin URL."
                                );
                            }

                            logEvent(
                                Enums.LogLevel.Info,
                                "Login required at " + response.signinButton.value
                            );

                            if (this.onShowSigninPrompt) {
                                // Bypass the built-in auth prompt if the host app handles it
                                this.onShowSigninPrompt(this, request, response.signinButton);
                            } else {
                                this.showAuthCodeInputDialog(request);

                                const left =
                                    window.screenX +
                                    (window.outerWidth - GlobalSettings.applets.authPromptWidth) /
                                        2;
                                const top =
                                    window.screenY +
                                    (window.outerHeight - GlobalSettings.applets.authPromptHeight) /
                                        2;

                                window.open(
                                    response.signinButton.value,
                                    response.signinButton.title
                                        ? response.signinButton.title
                                        : "Sign in",
                                    `width=${GlobalSettings.applets.authPromptWidth},height=${GlobalSettings.applets.authPromptHeight},left=${left},top=${top}`
                                );
                            }
                        }
                    } else {
                        logEvent(
                            Enums.LogLevel.Error,
                            "Authentication failed. Giving up after " +
                                request.attemptNumber +
                                " attempt(s)"
                        );

                        alert(Strings.magicCodeInputCard.authenticationFailed());
                    }

                    // Exit the loop. After a LoginRequestResponse, the host app is responsible for retrying the request
                    break;
                } else {
                    throw new Error("Unhandled response type: " + JSON.stringify(response));
                }
            }
        }
    }

    readonly renderedElement: HTMLElement;

    hostConfig?: HostConfig;
    channelAdapter?: ChannelAdapter;

    onCardChanging?: (sender: AdaptiveApplet, card: any) => boolean;
    onCardChanged?: (sender: AdaptiveApplet) => void;
    onPrefetchSSOToken?: (
        sender: AdaptiveApplet,
        tokenExchangeResource: TokenExchangeResource
    ) => void;
    onSSOTokenNeeded?: (
        sender: AdaptiveApplet,
        request: IActivityRequest,
        tokenExchangeResource: TokenExchangeResource
    ) => boolean;
    onPrepareActivityRequest?: (
        sender: AdaptiveApplet,
        request: IActivityRequest,
        action: ExecuteAction
    ) => boolean;
    onActivityRequestSucceeded?: (
        sender: AdaptiveApplet,
        response: SuccessResponse,
        parsedContent: string | AdaptiveCard | undefined
    ) => void;
    onActivityRequestFailed?: (sender: AdaptiveApplet, response: ErrorResponse) => number;
    onCreateSerializationContext?: (sender: AdaptiveApplet) => SerializationContext;
    onCreateProgressOverlay?: (
        sender: AdaptiveApplet,
        request: IActivityRequest
    ) => HTMLElement | undefined;
    onRemoveProgressOverlay?: (sender: AdaptiveApplet, request: IActivityRequest) => void;
    onRenderManualRefreshButton?: (sender: AdaptiveApplet) => HTMLElement | undefined;
    onAction?: (sender: AdaptiveApplet, action: Action) => void;
    onShowManualRefreshButton?: (sender: AdaptiveApplet) => boolean;
    onShowAuthCodeInputDialog?: (sender: AdaptiveApplet, request: IActivityRequest) => boolean;
    onShowSigninPrompt?: (
        sender: AdaptiveApplet,
        request: IActivityRequest,
        signinButton: AuthCardButton
    ) => void;

    constructor() {
        this.renderedElement = document.createElement("div");
        this.renderedElement.className = "aaf-cardHost";
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
            this.internalExecuteAction(this._card.refresh.action, ActivityRequestTrigger.Manual, 0);
        }
    }

    setCard(payload: any) {
        this.internalSetCard(payload, 0);
    }

    get card(): AdaptiveCard | undefined {
        return this._card;
    }
}
