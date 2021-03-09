import { Authentication, AuthCardButton, ExecuteAction, TokenExchangeResource } from "./card-elements";

export enum ActivityRequestTrigger {
    Automatic = "automatic",
    Manual = "manual",
}

export interface IActivityRequest {
    readonly action: ExecuteAction;
    readonly trigger: ActivityRequestTrigger;
    readonly attemptNumber: number;
    readonly consecutiveRefreshes: number;

    authCode?: string;
    token?: string;

    retryAsync(): void;
}

export class ActivityRequestError {
    constructor(readonly code?: string, readonly message?: string) { }
}

export abstract class ActivityResponse {
    constructor(readonly request: IActivityRequest) { }
}

export class SuccessResponse extends ActivityResponse {
    constructor(readonly request: IActivityRequest, readonly rawContent?: string) {
        super(request);
    }
}

export class ErrorResponse extends ActivityResponse {
    constructor(readonly request: IActivityRequest, readonly error: ActivityRequestError) {
        super(request);
    }
}

export class LoginRequestResponse extends ActivityResponse {
    readonly signinButton?: AuthCardButton;

    constructor(readonly request: IActivityRequest, private _auth: Authentication) {
        super(request);

        for (let button of this._auth.buttons) {
            if (button.type === "signin" && button.value !== undefined) {
                try {
                    new URL(button.value);

                    this.signinButton = button;

                    break;
                }
                catch (e) {
                    // Ignore parsing error
                }
            }
        }
    }

    get tokenExchangeResource(): TokenExchangeResource | undefined {
        return this._auth.tokenExchangeResource;
    }

    /*
    get signinButtonTitle(): string | undefined {
        return this._signinButton ? this._signinButton.title : undefined;
    }

    get signinButtonImage(): string | undefined {
        return this._signinButton ? this._signinButton.image : undefined;
    }

    get signinUrl(): string | undefined {
        return this._signinButton ? this._signinButton.value : undefined;
    }
    */
}

export class InvalidAuthCodeResponse extends ActivityResponse { }

export class PreconditionFailedResponse extends ActivityResponse {
    constructor(readonly request: IActivityRequest, readonly error: ActivityRequestError) {
        super(request);
    }
}