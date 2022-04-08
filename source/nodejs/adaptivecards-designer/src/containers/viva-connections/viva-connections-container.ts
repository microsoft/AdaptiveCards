// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";
import * as hostConfigLight from "../../hostConfigs/viva-connections-light.json";
import * as hostConfigDark from "../../hostConfigs/viva-connections-dark.json";

abstract class VivaConnectionsContainer extends HostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("vivaConnectionsContainer");

        let vcContainer = document.createElement("div");
        vcContainer.className = "vivaConnectionsContainer";
        vcContainer.appendChild(this.cardHost);

        hostElement.appendChild(vcContainer);
    }

    get targetVersion(): Adaptive.Version {
        return Adaptive.Versions.v1_3;
    }
}

export class LightVivaConnectionsContainer extends VivaConnectionsContainer {
	public getHostConfig(): Adaptive.HostConfig {
			return new Adaptive.HostConfig(hostConfigLight);
	}
}

export class DarkVivaConnectionsContainer extends VivaConnectionsContainer {
	public getBackgroundColor(): string {
			return "#1b1a19";
	}

	public getHostConfig(): Adaptive.HostConfig {
			return new Adaptive.HostConfig(hostConfigDark);
	}
}