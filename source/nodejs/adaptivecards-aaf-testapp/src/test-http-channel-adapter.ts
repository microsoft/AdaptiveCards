import * as Adaptive from "adaptivecards";
import { ActivityRequestError, Authentication, CardButton, ErrorResponse, LoginRequestResponse, SuccessResponse, TokenExchangeResource } from "adaptivecards";

export class TestHttpChannelAdapter extends Adaptive.ChannelAdapter {
    constructor(readonly url: string) {
        super();
    }

    async sendRequestAsync(request: Adaptive.IActivityRequest): Promise<Adaptive.ActivityResponse> {
        if (request.action.verb === "localException") {
            throw new Error("Local exception");
        }

        if (request.action.verb === "remoteFailedUnauthenticated") {
            let auth = new Authentication();
            auth.text = "prop_text";
            auth.connectionName = "prop_connectionName";

            auth.tokenExchangeResource = new TokenExchangeResource();
            auth.tokenExchangeResource.id = "prop_id";
            auth.tokenExchangeResource.providerId = "prop_providerId";
            auth.tokenExchangeResource.uri = "https://somewhere.under.the.rainbow"

            let button = new CardButton();
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
    }
}