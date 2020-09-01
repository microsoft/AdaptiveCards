import * as Adaptive from "adaptivecards";

export class TestHttpChannelAdapter extends Adaptive.HttpChannelAdapter {
    async sendRequestAsync(request: Adaptive.ActivityRequest): Promise<Adaptive.ActivityResponse> {
        if (request.activity.value.action.verb === "localException") {
            throw new Error("Local exception");
        }

        return super.sendRequestAsync(request);
    }
}
