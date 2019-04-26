// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { HostContainer } from "./host-container";
import {
    AdaptiveCard,
    HostConfig,
    Size,
    TextSize,
    TextColor,
    TextWeight,
    Spacing,
    ShowCardActionMode,
    Orientation,
    ActionAlignment,
} from "adaptivecards";
import * as skypeConfiguration from "../../../../../samples/HostConfig/skype.json";

export class SkypeContainer extends HostContainer {
    private _width: number;

    protected renderContainer(adaptiveCard: AdaptiveCard, target: HTMLElement): HTMLElement {
        var element = document.createElement("div");
        element.className = "skypeContainer";

        // Draw the hexagon bot logo
        var botElement = document.createElement("div");
        botElement.className = "hexagon";

        var botElementIn1 = document.createElement("div");
        botElementIn1.className = "hexagon-in1";
        botElement.appendChild(botElementIn1);

        var botElementIn2 = document.createElement("div");
        botElementIn2.className = "hexagon-in2";
        botElementIn1.appendChild(botElementIn2);

        var cardWrapper = document.createElement("div");
        cardWrapper.style.width = this._width + "px";

        element.appendChild(botElement);
        element.appendChild(cardWrapper);
        target.appendChild(element);

        var renderedCard = adaptiveCard.render(cardWrapper);

        return element;
    }

    constructor(width: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
    }

    public getHostConfig(): HostConfig {
        return new HostConfig(skypeConfiguration);
    }
}
