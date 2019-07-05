// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";
import * as hostConfig from "../../hostConfigs/webchat.json";

export class WebChatContainer extends HostContainer {
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
}
