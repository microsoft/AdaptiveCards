import { ActivityResponse, IActivityRequest } from "./activity-request";

export abstract class ChannelAdapter {
    abstract sendRequestAsync(request: IActivityRequest): Promise<ActivityResponse>;
}
