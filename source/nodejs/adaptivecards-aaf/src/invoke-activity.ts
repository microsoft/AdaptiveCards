export interface InvokeActivity {
    type: "invoke",
    name: "adaptiveCard/action",
    channelId?: string,
    localTimezone: string,
    localTimestamp: string,
    from?: {
        id: string
    },
    conversation?: {
        id: string
    },
    replyToId?: string, // Remove?
    entities?: object[],
    channelData?: object,
    serviceUrl?: string, // Remove?
    value: {
        action: {
            type: "Action.Execute",
            id?: string,
            verb: string,
            data?: object
        },
        trigger: ActivityInvocationTrigger,
        magicCode?: string
    },
    relatesTo?: string
}

export enum ActivityInvocationTrigger {
    Automatic = "automatic",
    Manual = "manual",
}

export interface ActivityRequest {
    readonly activity: InvokeActivity,
    attemptNumber: number,
    consecutiveRefreshes: number
}

export enum ActivityStatus {
    Success,
    Failure
}

export interface ActivityResponse {
    readonly request: ActivityRequest,
    readonly status: ActivityStatus,
    content: any
}
