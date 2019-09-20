// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";
import * as hostConfig from "../../hostConfigs/windows-notification.json";

export class ToastContainer extends HostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("toast-card");

        let frame = document.createElement("div");
        frame.className = "toast-frame";
        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfig);
    }
}
