// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer, ColorTheme } from "../host-container";
import * as hostConfigLight from "../../hostConfigs/microsoft-teams-light.json";
import * as hostConfigDark from "../../hostConfigs/microsoft-teams-dark.json";

export class TeamsContainer extends HostContainer {
    private _colorTheme: ColorTheme;

    constructor(theme: ColorTheme) {
        super("Microsoft Teams", `containers/teams-container-${theme.toLowerCase()}.css`);
        this._colorTheme = theme;
    }

    public renderTo(hostElement: HTMLElement) {
        var outerFrame = document.createElement("div");
        outerFrame.className = "teams-frame";

        // Draw the hexagon bot logo
        var hexagonOuter = document.createElement("div");
        hexagonOuter.className = "teams-hexagon-outer";

        var hexagonInner = document.createElement("div");
        hexagonInner.className = "teams-hexagon-inner";

        var botLogo = document.createElement("div");
        botLogo.className = "teams-bot-logo";

        hexagonOuter.appendChild(hexagonInner);
        hexagonInner.appendChild(botLogo);

        outerFrame.appendChild(hexagonOuter);

        let innerFrame = document.createElement("div");
        innerFrame.className = "teams-inner-frame";

        this.cardHost.classList.add("teams-card");

        let botNameAndTime = document.createElement("div");
        botNameAndTime.className = "teams-botNameAndTime";
        botNameAndTime.innerText = "Test Bot    2:36 PM";

        innerFrame.appendChild(botNameAndTime);
        innerFrame.appendChild(this.cardHost);

        outerFrame.appendChild(innerFrame);

        hostElement.appendChild(outerFrame);
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
        return Adaptive.Versions.v1_4;
    }

    get enableDeviceEmulation(): boolean {
        return true;
    }

    set colorTheme(value: ColorTheme) {
        this._colorTheme = value;
        this.styleSheet = `containers/teams-container-${this._colorTheme.toLowerCase()}.css`;
    }

    get supportsMultipleThemes(): boolean {
        return true;
    }
}
