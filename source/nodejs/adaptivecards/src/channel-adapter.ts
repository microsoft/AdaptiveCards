import { ActivityResponse, ActivityRequest } from "./activity-request";

export abstract class ChannelAdapter {
    abstract sendRequestAsync(request: ActivityRequest): Promise<ActivityResponse>;
}
