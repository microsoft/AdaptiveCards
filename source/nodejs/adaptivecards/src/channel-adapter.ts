// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { ActivityResponse, IActivityRequest } from "./activity-request";

export abstract class ChannelAdapter {
    abstract sendRequestAsync(request: IActivityRequest): Promise<ActivityResponse>;
}
