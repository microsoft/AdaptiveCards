
export class AdaptiveCMSEntryInstance {
    updatedAt?:      Date;
    state?:          string;
    isShareable?:    boolean;
    json?:           JSON;
    version?:        string;
    author?:         string;
}

export class AdaptiveCMSEntry {
    id:              string;
    authors?:         string[];
    tags?:            string[];
    deletedVersions?: any[];
    isLive?:          boolean;
    name?:            string;
    instances?:       AdaptiveCMSEntryInstance[];
    updatedAt?:       Date;
    createdAt?:       Date;
}
