// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { MultiThemeHostContainer } from "../multi-theme-host-container";
import * as hostConfigLight from "../../hostConfigs/berlin-light.json";
import * as hostConfigDark from "../../hostConfigs/berlin-dark.json";

export enum ContainerSize {
    Small = "Small",
    Medium = "Medium",
    Large = "Large"
}

export class BerlinContainer extends MultiThemeHostContainer {
    private _containerSize: ContainerSize;

    constructor(size: ContainerSize) {
        super(
            "Berlin (Test)",
            "berlin-container",
            hostConfigLight,
            hostConfigDark,
            "#D2D2D2",
            "#616161"
        );
        this._containerSize = size;
    }

    public initialize(): void {
        super.initialize();
        Adaptive.GlobalSettings.removePaddingFromContainersWithBackgroundImage = true;
    }

    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.remove(
            "berlin-small-card",
            "berlin-medium-card",
            "berlin-large-card"
        );
        this.cardHost.classList.add(`berlin-${this._containerSize.toLowerCase()}-card`);
        const outerFrame = document.createElement("div");
        outerFrame.classList.add("berlin-outer-container");
        outerFrame.classList.add(`berlin-${this._containerSize.toLowerCase()}-container`);

        const header = document.createElement("div");
        header.className = "berlin-header";
        outerFrame.appendChild(header);

        const headerText = document.createElement("p");
        headerText.className = "berlin-header-text";
        headerText.textContent = "Berlin Header";
        header.appendChild(headerText);

        const moreButton = document.createElement("div");
        moreButton.className = "berlin-header-more-button";
        moreButton.setAttribute("role", "button");
        moreButton.tabIndex = 0;
        header.appendChild(moreButton);

        const innerFrame = document.createElement("div");
        innerFrame.className = "berlin-inner-container";
        innerFrame.appendChild(this.cardHost);

        outerFrame.appendChild(innerFrame);
        hostElement.appendChild(outerFrame);
    }

    get targetVersion(): Adaptive.Version {
        return Adaptive.Versions.v1_6;
    }

    get isFixedHeight(): boolean {
        return true;
    }

    set containerSize(value: ContainerSize) {
        this._containerSize = value;
    }

    get supportsMultipleSizes(): boolean {
        return true;
    }

    static get supportedContainerSizes(): string[] {
        return Object.values(ContainerSize);
    }
}
