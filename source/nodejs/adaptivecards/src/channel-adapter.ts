import { ActivityResponse, ActivityRequest } from "./invoke-activity";

export abstract class ChannelAdapter {
    abstract sendRequestAsync(request: ActivityRequest): Promise<ActivityResponse>;
}
