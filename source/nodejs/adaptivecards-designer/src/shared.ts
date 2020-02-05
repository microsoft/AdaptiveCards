import * as Adaptive from "adaptivecards";

export class GlobalSettings {
    static enableDataBindingSupport: boolean = false;
    static showDataStructureToolbox: boolean = false;
    static showSampleDataEditorToolbox: boolean = false;
    static showVersionPicker: boolean = false;
}

export type TargetVersion = Adaptive.Version | "*";

export class Versions {
    static readonly v1_0 = new Adaptive.Version(1, 0);
    static readonly v1_1 = new Adaptive.Version(1, 1);
    static readonly v1_2 = new Adaptive.Version(1, 2);
    static readonly latest = Versions.v1_2;
    static readonly vNext = new Adaptive.Version(1000, 0, "vNext");
}

export var SupportedTargetVersions: Adaptive.Version[] = [ Versions.v1_0, Versions.v1_1, Versions.v1_2, Versions.vNext ];

export function isVersionLessOrEqual(version: TargetVersion, targetVersion: TargetVersion): boolean {
    if (version instanceof Adaptive.Version) {
        if (targetVersion instanceof Adaptive.Version) {
            return targetVersion.compareTo(version) >= 0;
        }
        else {
            // Target version is *
            return true;
        }
    }
    else {
        // Version is *
        return true;
    }
}