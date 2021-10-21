// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";
import * as hostConfig from "../../hostConfigs/viva-connections.json";

export class VivaConnectionsContainer extends HostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("vivaConnectionsContainer");

        let vcContainer = document.createElement("div");
        vcContainer.className = "vivaConnectionsContainer";
        vcContainer.appendChild(this.cardHost);

        hostElement.appendChild(vcContainer);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfig);
    }

    get targetVersion(): Adaptive.Version {
        return Adaptive.Versions.v1_3;
    }
}
