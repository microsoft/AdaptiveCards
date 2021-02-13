// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";
import * as hostConfigLight from "../../hostConfigs/cortana-skills-light.json";
import * as hostConfigDark from "../../hostConfigs/cortana-skills-dark.json";

abstract class BaseCortanaContainer extends HostContainer {
    public renderTo(hostElement: HTMLElement) {
        var frame = document.createElement("div");

        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }

    get targetVersion(): Adaptive.Version {
        return Adaptive.Versions.v1_2;
    }
}

export class LightCortanaContainer extends BaseCortanaContainer {
    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfigLight);
    }
}

export class DarkCortanaContainer extends BaseCortanaContainer {
    public getBackgroundColor(): string {
        return "#201E1F";
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfigDark);
    }
}
