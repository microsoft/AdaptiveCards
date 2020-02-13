import { ActivityResponse, ActivityRequest } from "./invoke-activity";

export abstract class ChannelAdapter {
    abstract async sendRequestAsync(activity: ActivityRequest): Promise<ActivityResponse>;
}
