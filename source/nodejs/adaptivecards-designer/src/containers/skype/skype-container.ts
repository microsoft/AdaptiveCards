// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";
import * as hostConfig from "../../hostConfigs/skype.json";

export class SkypeContainer extends HostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("skype-card");

        var frame = document.createElement("div");
        frame.className = "skype-frame";

        // Draw the hexagon bot logo
        var hexagonOuter = document.createElement("div");
        hexagonOuter.className = "skype-hexagon-outer";

        var hexagonInner = document.createElement("div");
        hexagonInner.className = "skype-hexagon-inner";

        var botLogo = document.createElement("div");
        botLogo.className = "skype-bot-logo";

        hexagonOuter.appendChild(hexagonInner);
        hexagonInner.appendChild(botLogo);

        frame.appendChild(hexagonOuter);
        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfig);
    }
}
