// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { SingleThemeHostContainer } from "../single-theme-host-container";
import * as hostConfig from "../../hostConfigs/render-to-image.json";

export class BotFrameworkContainer extends SingleThemeHostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("bf-images-card");

        let frame = document.createElement("div");
        frame.className = "bf-images-frame";
        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfig);
    }

    get enableDeviceEmulation(): boolean {
        return true;
    }
}
