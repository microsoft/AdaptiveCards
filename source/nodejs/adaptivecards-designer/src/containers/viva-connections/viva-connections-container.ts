// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer, ColorTheme } from "../host-container";
import * as hostConfigLight from "../../hostConfigs/viva-connections-light.json";
import * as hostConfigDark from "../../hostConfigs/viva-connections-dark.json";

export class VivaConnectionsContainer extends HostContainer {
    private _colorTheme: ColorTheme;

    constructor(theme: ColorTheme) {
        super(
            "Viva Connections",
            `containers/viva-connections-container-${theme.toLowerCase()}.css`
        );
        this._colorTheme = theme;
    }

    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("vivaConnectionsContainer");

        let vcContainer = document.createElement("div");
        vcContainer.className = "vivaConnectionsContainer";
        vcContainer.appendChild(this.cardHost);

        hostElement.appendChild(vcContainer);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(
            this._colorTheme === ColorTheme.Light ? hostConfigLight : hostConfigDark
        );
    }

    public getBackgroundColor(): string {
        return this._colorTheme === ColorTheme.Light ? "#F6F6F6" : "#1b1a19";
    }

    get targetVersion(): Adaptive.Version {
        return Adaptive.Versions.v1_3;
    }

    set colorTheme(value: ColorTheme) {
        this._colorTheme = value;
        this.styleSheet = `containers/viva-connections-container-${this._colorTheme.toLowerCase()}.css`;
    }

    get supportsMultipleThemes(): boolean {
        return true;
    }
}
