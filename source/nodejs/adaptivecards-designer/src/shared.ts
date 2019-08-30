import * as Adaptive from "adaptivecards";

export class GlobalSettings {
    static previewFeaturesEnabled: boolean = false;
}

export var SupportedTargetVersions: Adaptive.Version[] = [
    Adaptive.Versions.v1_0,
    Adaptive.Versions.v1_1,
    Adaptive.Versions.v1_2,
    Adaptive.Versions.vNext
];