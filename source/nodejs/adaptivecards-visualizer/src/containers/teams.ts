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
import * as teamsLightConfiguration from "../../../../../samples/HostConfig/microsoft-teams-light.json";

export class TeamsContainer extends HostContainer {
    protected renderContainer(adaptiveCard: AdaptiveCard, target: HTMLElement): HTMLElement {
        var element = document.createElement("div");
        element.style.borderTop = "1px solid #F1F1F1";
        element.style.borderRight = "1px solid #F1F1F1";
        element.style.borderBottom = "1px solid #F1F1F1";
        element.style.border = "1px solid #F1F1F1"
        target.appendChild(element);

        adaptiveCard.render(element);

        return element;
    }

    public getHostConfig(): HostConfig {
        return new HostConfig(teamsLightConfiguration);
    }
}
