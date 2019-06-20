// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import * as Designer from "../../adaptivecards-designer";

var windowsTimelineConfiguration = require("../../../../../../samples/HostConfig/windows-timeline.json");

export class TimelineContainer extends Designer.HostContainer {
    public initialize() {
        Adaptive.AdaptiveCard.elementTypeRegistry.reset();
        Adaptive.AdaptiveCard.actionTypeRegistry.reset();

        Adaptive.AdaptiveCard.useMarkdownInRadioButtonAndCheckbox = true;
        Adaptive.AdaptiveCard.useAdvancedCardBottomTruncation = true;
        Adaptive.AdaptiveCard.useAdvancedTextBlockTruncation = true;
    }

    public renderTo(hostElement: HTMLElement) {
        let target = document.getElementById("designerHost");
        let frame = document.createElement("div");
        frame.className = "timeline-frame";
        target.appendChild(frame);

        let cardContainer = document.createElement("div");
        cardContainer.className = "timeline-card";
        frame.appendChild(cardContainer);

        this.cardHost.style.height = "100%";
        this.cardHost.style.width = "100%";
        this.cardHost.style.overflow = "hidden";

        cardContainer.appendChild(this.cardHost);
        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(windowsTimelineConfiguration);
    }

    get isFixedHeight(): boolean {
        return true;
    }
}
