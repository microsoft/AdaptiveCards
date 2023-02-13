import * as Adaptive from "adaptivecards";
import * as Shared from "./shared";
import { ActivityRequestError, ActivityResponse, AuthCardButton, Authentication, DataQuery, ErrorResponse, ExecuteAction, LoginRequestResponse, SuccessResponse, TokenExchangeResource } from "adaptivecards";

export class TestChannelAdapter extends Adaptive.ChannelAdapter {
    constructor(readonly url: string) {
        super();
    }

    async sendRequestAsync(request: Adaptive.IActivityRequest): Promise<Adaptive.ActivityResponse> {
        if (request.action instanceof ExecuteAction) {
            if (request.action.verb === "localException") {
                throw new Error("Local exception");
            }
    
            if (request.action.verb === "localFailSSO") {
                if (request.authToken === "valid_sso_token") {
                    // We have an SSO token
                    return new SuccessResponse(request, JSON.stringify(Shared.ssoSuccessCard));
                }
    
                let auth = new Authentication();
                auth.text = "prop_text";
                auth.connectionName = "prop_connectionName";
    
                auth.tokenExchangeResource = new TokenExchangeResource();
                auth.tokenExchangeResource.id = "prop_id";
                auth.tokenExchangeResource.providerId = "prop_providerId";
                auth.tokenExchangeResource.uri = "https://somewhere.under.the.rainbow"
    
                return new LoginRequestResponse(request, auth)
            }
    
            if (request.action.verb === "localFailOAuth") {
                if (request.authCode) {
                    if (request.authCode === "valid_auth_code") {
                        // We have an auth code
                        return new SuccessResponse(request, JSON.stringify(Shared.oauthSuccessCard));
                    }
    
                    return new ErrorResponse(request, new ActivityRequestError("401", "Invalid auth code."));
                }
    
                let auth = new Authentication();
                auth.text = "prop_text";
                auth.connectionName = "prop_connectionName";
    
                let button = new AuthCardButton();
                button.type = "signin";
                button.value = "http://www.microsoft.com";
    
                auth.buttons = [ button ];
    
                return new LoginRequestResponse(request, auth)
            }
    
            if (request.attemptNumber < 3) {
                return new ErrorResponse(request, new ActivityRequestError(undefined, "Deliberately failing attempt " + request.attemptNumber.toString()));
            }
    
            let activity = {
                type: "invoke",
                name: "adaptiveCard/action",
                localTimezone: "",
                localTimestamp: "",
                value: {
                    action: {
                        type: "Action.Execute",
                        id: request.action.id,
                        verb: request.action.verb,
                        data: request.action.data
                    },
                    trigger: request.trigger,
                }
            };
    
            let response = await fetch(
                this.url,
                {
                    method: "POST",
                    headers: {
                        "Content-Type": "application/json"
                    },
                    body: JSON.stringify(activity)
                }
            )
    
            if (response.status === 200) {
                return new SuccessResponse(request, await response.text());
            }
            else {
                return new ErrorResponse(request, new ActivityRequestError(undefined, response.statusText));
            }
        } else if (request.action instanceof DataQuery) {
            const response = [
                { title: "Matt", value: "1" },
                { title: "Mark", value: "2" },
                { title: "Mack", value: "3" },
                { title: "May", value: "4" },
            ];              
            return new SuccessResponse(request, JSON.stringify(response));
        }
    }
}