// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";

var renderToImageConfiguration = require("../../../../../../samples/HostConfig/render-to-image.json");

export class BotFrameworkContainer extends HostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("bf-images-card");

        let frame = document.createElement("div");
        frame.className = "bf-images-frame";
        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(renderToImageConfiguration);
    }
}
