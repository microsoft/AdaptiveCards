// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { MultiThemeHostContainer } from "../multi-theme-host-container";
import * as hostConfigLight from "../../hostConfigs/cortana-skills-light.json";
import * as hostConfigDark from "../../hostConfigs/cortana-skills-dark.json";

export class CortanaContainer extends MultiThemeHostContainer {
    constructor() {
        super(
            "Cortana Skills",
            "cortana-container",
            hostConfigLight,
            hostConfigDark,
            "#F6F6F6",
            "#201E1F"
        );
    }

    public renderTo(hostElement: HTMLElement) {
        var frame = document.createElement("div");

        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }

    get targetVersion(): Adaptive.Version {
        return Adaptive.Versions.v1_2;
    }

    get enableDeviceEmulation(): boolean {
        return true;
    }
}
