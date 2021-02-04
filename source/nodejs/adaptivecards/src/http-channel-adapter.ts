import { ChannelAdapter } from "./channel-adapter";
import { ActivityRequest, ActivityResponse, ActivityStatus } from "./invoke-activity";

export class HttpChannelAdapter extends ChannelAdapter {
    constructor(readonly url: string) {
        super();
    }

    async sendRequestAsync(request: ActivityRequest): Promise<ActivityResponse> {
        let response = await fetch(
            this.url,
            {
                method: "POST",
                headers: {
                    "Content-Type": "application/json"
                },
                body: JSON.stringify(request.activity)
            }
        )

        if (response.status === 200) {
            return {
                request: request,
                status: ActivityStatus.Success,
                content: await response.text()
            };
        }
        else {
            return {
                request: request,
                status: ActivityStatus.Failure,
                content: response.statusText
            }
        }
    }
}
