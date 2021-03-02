import { AdaptiveCard, Authentication, ExecuteAction } from "./card-elements";

export enum ActivityRequestTrigger {
    Automatic = "automatic",
    Manual = "manual",
}

/*
export enum ActivityStatus {
    Success,
    Error,
    LoginRequest,
    IncorrectAuthCode,
    PreconditionFailed
}
*/

export interface ActivityRequest {
    readonly action: ExecuteAction,
    readonly trigger: ActivityRequestTrigger,
    authCode?: string,
    attemptNumber: number,
    consecutiveRefreshes: number
}

export class ActivityRequestError {
    constructor(readonly code?: string, readonly message?: string) { }
}

/*
export interface ActivityResponse {
    readonly request: ActivityRequest,
    readonly status: ActivityStatus,
    content?: string | ActivityRequestError | Authentication
}
*/

export abstract class ActivityResponse {
    constructor(readonly request: ActivityRequest) { }
}

export class SuccessResponse extends ActivityResponse {
    constructor(readonly request: ActivityRequest, readonly rawContent?: string) {
        super(request);
    }
}

export class ErrorResponse extends ActivityResponse {
    constructor(readonly request: ActivityRequest, readonly error: ActivityRequestError) {
        super(request);
    }
}

export class LoginRequestResponse extends ActivityResponse {
    constructor(readonly request: ActivityRequest, readonly auth: Authentication) {
        super(request);
    }

    getSinginUrl(): string | undefined {
        for (let button of this.auth.buttons) {
            if (button.type === "singin") {
                return button.value;
            }
        }

        return undefined;
    }
}

export class InvalidAuthCodeResponse extends ActivityResponse { }

export class PreconditionFailedResponse extends ActivityResponse {
    constructor(readonly request: ActivityRequest, readonly error: ActivityRequestError) {
        super(request);
    }
}