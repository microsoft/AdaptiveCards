import { Authentication, CardButton, ExecuteAction } from "./card-elements";

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

    trySendAsync(): void;
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
    private static getSinginButton(auth: Authentication): CardButton | undefined {
        for (let button of auth.buttons) {
            if (button.type === "signin" && button.value !== undefined) {
                try {
                    let parsedUrl = new URL(button.value);

                    return button;
                }
                catch (e) {
                    return undefined;
                }
            }
        }

        return undefined;
    }

    private _signinButton?: CardButton;

    constructor(readonly request: IActivityRequest, auth: Authentication) {
        super(request);

        this._signinButton = LoginRequestResponse.getSinginButton(auth);
    }

    get signinButtonTitle(): string | undefined {
        return this._signinButton ? this._signinButton.title : undefined;
    }

    get signinButtonImage(): string | undefined {
        return this._signinButton ? this._signinButton.image : undefined;
    }

    get signinUrl(): string | undefined {
        return this._signinButton ? this._signinButton.value : undefined;
    }
}

export class InvalidAuthCodeResponse extends ActivityResponse { }

export class PreconditionFailedResponse extends ActivityResponse {
    constructor(readonly request: IActivityRequest, readonly error: ActivityRequestError) {
        super(request);
    }
}