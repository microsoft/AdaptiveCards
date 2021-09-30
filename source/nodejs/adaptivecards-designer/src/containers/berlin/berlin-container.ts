// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";
import * as hostConfigLight from "../../hostConfigs/berlin-light.json";
import * as hostConfigDark from "../../hostConfigs/berlin-dark.json";

export class BaseBerlinContainer extends HostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("berlinOuterContainer");

        let frame = document.createElement("div");
        frame.className = "berlinInnerContainer";
        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }
    get targetVersion(): Adaptive.Version {
        return Adaptive.Versions.v1_4;
    }
}

export class LightBerlinContainer extends BaseBerlinContainer {
    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfigLight);
    }
}

export class DarkBerlinContainer extends BaseBerlinContainer {
	public getBackgroundColor(): string {
        return "#201E1F";
    }

	public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfigDark);
    }
}
