import * as Adaptive from "adaptivecards";

export class GlobalSettings {
    static enableDataBindingSupport: boolean = false;
    static showDataStructureToolbox: boolean = false;
    static showSampleDataEditorToolbox: boolean = false;
    static showSampleHostDataEditorToolbox: boolean = false;
    static showVersionPicker: boolean = false;
    static selectedHostContainerControlsTargetVersion: boolean = true;
    static showTargetVersionMismatchWarning: boolean = true;
    static supportedTargetVersions: Adaptive.Version[] = Adaptive.Versions.getAllDeclaredVersions();
}
