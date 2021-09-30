// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { HostContainer } from "./host-container";
import {
    AdaptiveCard,
    HostConfig,
} from "adaptivecards";
import * as berlinConfiguration from "../../../../../samples/HostConfig/berlin-light.json";

export class BerlinContainer extends HostContainer {
    private _width: number;

    private _height: number;

    protected renderContainer(adaptiveCard: AdaptiveCard, target: HTMLElement): HTMLElement {
        var outerElement = document.createElement("div");
        outerElement.className = "berlinOuterContainer";

        var innerElement = document.createElement("div");
        innerElement.className = "berlinInnerContainer";

        target.appendChild(outerElement);
        outerElement.appendChild(innerElement);

        var renderedCard = adaptiveCard.render();
        innerElement.appendChild(renderedCard);

        return outerElement;
    }

    constructor(width: number, height: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
        this._height = height;
    }

    public getHostConfig(): HostConfig {
        return new HostConfig(berlinConfiguration);
    }
}
