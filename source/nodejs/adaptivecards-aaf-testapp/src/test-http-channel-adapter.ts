import * as Adaptive from "adaptivecards";
import { ActivityRequestError, ErrorResponse, SuccessResponse } from "adaptivecards";

export class TestHttpChannelAdapter extends Adaptive.ChannelAdapter {
    constructor(readonly url: string) {
        super();
    }

    async sendRequestAsync(request: Adaptive.ActivityRequest): Promise<Adaptive.ActivityResponse> {
        if (request.action.verb === "localException") {
            throw new Error("Local exception");
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