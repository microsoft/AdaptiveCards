// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer, ColorTheme } from "../host-container";
import * as hostConfigLight from "../../hostConfigs/cortana-skills-light.json";
import * as hostConfigDark from "../../hostConfigs/cortana-skills-dark.json";

export class CortanaContainer extends HostContainer {
    private _colorTheme: ColorTheme;

    constructor(theme: ColorTheme) {
        super("Cortana Skills", `containers/cortana-container-${theme.toLowerCase()}.css`);
        this._colorTheme = theme;
    }

    public renderTo(hostElement: HTMLElement) {
        var frame = document.createElement("div");

        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(
            this._colorTheme === ColorTheme.Light ? hostConfigLight : hostConfigDark
        );
    }

    public getBackgroundColor(): string {
        return this._colorTheme === ColorTheme.Light ? "#F6F6F6" : "#201E1F";
    }

    get targetVersion(): Adaptive.Version {
        return Adaptive.Versions.v1_2;
    }

    get enableDeviceEmulation(): boolean {
        return true;
    }

    set colorTheme(value: ColorTheme) {
        this._colorTheme = value;
        this.styleSheet = `containers/cortana-container-${this._colorTheme.toLowerCase()}.css`;
    }

    get supportsMultipleThemes(): boolean {
        return true;
    }
}
