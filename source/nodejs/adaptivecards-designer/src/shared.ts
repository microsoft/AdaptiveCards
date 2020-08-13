import * as Adaptive from "adaptivecards";

export class GlobalSettings {
    static enableDataBindingSupport: boolean = false;
    static showDataStructureToolbox: boolean = false;
    static showSampleDataEditorToolbox: boolean = false;
    static showVersionPicker: boolean = false;
    static selectedHostContainerControlsTargetVersion: boolean = true;
    static showTargetVersionMismatchWarning: boolean = true;
}

export var SupportedTargetVersions: Adaptive.Version[] = [
    Adaptive.Versions.v1_0,
    Adaptive.Versions.v1_1,
    Adaptive.Versions.v1_2,
    Adaptive.Versions.v1_3
];
