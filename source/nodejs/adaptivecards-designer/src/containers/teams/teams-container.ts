// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import * as Designer from "../../adaptivecards-designer";

var teamsDarkConfiguration = require("../../../../../../samples/HostConfig/microsoft-teams-dark.json");
var teamsLightConfiguration = require("../../../../../../samples/HostConfig/microsoft-teams-light.json");

export abstract class BaseTeamsContainer extends Designer.HostContainer {
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
}

export class LightTeamsContainer extends BaseTeamsContainer {
    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(teamsLightConfiguration);
    }
}

export class DarkTeamsContainer extends BaseTeamsContainer {
    public getBackgroundColor(): string {
        return "#201E1F";
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(teamsDarkConfiguration);
    }
}
