// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { SingleThemeHostContainer } from "../single-theme-host-container";
import * as hostConfig from "../../hostConfigs/webchat.json";

export class WebChatContainer extends SingleThemeHostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("webChatOuterContainer");

        let frame = document.createElement("div");
        frame.className = "webChatInnerContainer";
        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfig);
    }

    get targetVersion(): Adaptive.Version {
        return Adaptive.Versions.v1_3;
    }
}
