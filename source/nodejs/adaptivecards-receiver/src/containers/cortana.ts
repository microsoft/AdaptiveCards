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
import * as cortanaConfiguration from "../../../../../samples/HostConfig/cortana-skills.json";

export class CortanaContainer extends HostContainer {

    private _renderFrame: boolean;

    constructor(renderFrame: boolean, styleSheet: string) {
        super(styleSheet);

        this._renderFrame = renderFrame;
    }

    protected renderContainer(adaptiveCard: AdaptiveCard, target: HTMLElement): HTMLElement {

        var wrapper = document.createElement("div");

        var cardContainer = document.createElement("div");

        if (this._renderFrame) {
            wrapper.className = "cortanaFrame";
            cardContainer.className = "cardWrapper";
        }

        adaptiveCard.render(cardContainer);

        wrapper.appendChild(cardContainer);
        target.appendChild(wrapper);

        return cardContainer;
    }

    public getHostConfig(): HostConfig {
        return new HostConfig(cortanaConfiguration);
    }
}
