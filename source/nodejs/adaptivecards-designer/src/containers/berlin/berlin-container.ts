// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer, ColorTheme } from "../host-container";
import * as hostConfigLight from "../../hostConfigs/berlin-light.json";
import * as hostConfigDark from "../../hostConfigs/berlin-dark.json";

export enum ContainerSize {
    Small = "Small",
    Medium = "Medium",
    Large = "Large"
};

export class BerlinContainer extends HostContainer {
    private _containerSize: ContainerSize;
    private _colorTheme: ColorTheme;

    constructor(size: ContainerSize, theme: ColorTheme) {
        super("Berlin (Test)",
            `containers/berlin-container-${theme.toLowerCase()}.css`);
        this._containerSize = size;
        this._colorTheme = theme;
    }

    public initialize(): void {
        super.initialize();
        Adaptive.GlobalSettings.removePaddingFromContainersWithBackgroundImage = true; 
    }

    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.remove("berlin-small-card", "berlin-medium-card", "berlin-large-card");
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

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig((this._colorTheme === ColorTheme.Light) ? hostConfigLight : hostConfigDark);
    }

    public getBackgroundColor(): string {
        return this._colorTheme === ColorTheme.Light ? "#D2D2D2" : "#616161";
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

    set colorTheme(value: ColorTheme) {
        this._colorTheme = value;
        this.styleSheet = `containers/berlin-container-${this._colorTheme.toLowerCase()}.css`
    }

    get supportsMultipleSizes(): boolean {
        return true;
    }

    get supportsMultipleThemes(): boolean {
        return true;
    }
	
    static get supportedContainerSizes(): string[] {
        return Object.values(ContainerSize);
    }
}
