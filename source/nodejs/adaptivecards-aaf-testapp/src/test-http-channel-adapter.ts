import * as AAF from "adaptivecards-aaf";

export class TestHttpChannelAdapter extends AAF.HttpChannelAdapter {
    async sendRequestAsync(request: AAF.ActivityRequest): Promise<AAF.ActivityResponse> {
        if (request.activity.value.action.verb === "localException") {
            throw new Error("Local exception");
        }

        return super.sendRequestAsync(request);
    }
}
