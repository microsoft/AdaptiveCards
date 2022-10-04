// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { MultiThemeHostContainer } from "../multi-theme-host-container";
import * as hostConfigLight from "../../hostConfigs/viva-connections-light.json";
import * as hostConfigDark from "../../hostConfigs/viva-connections-dark.json";

export class VivaConnectionsContainer extends MultiThemeHostContainer {
    constructor() {
        super(
            "Viva Connections",
            "viva-connections-container",
            hostConfigLight,
            hostConfigDark,
            "#F6F6F6",
            "#1b1a19"
        );
    }

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
