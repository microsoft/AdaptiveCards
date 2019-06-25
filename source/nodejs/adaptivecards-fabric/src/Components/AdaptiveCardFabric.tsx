// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as ReactDOM from "react-dom";
import * as AC from "adaptivecards";
import { initializeIcons, FocusZone, FocusZoneDirection, FocusZoneTabbableElements } from "office-ui-fabric-react";
import * as Components from ".";
import * as Actions from "../Actions";
import { getDiv } from "../Utils/shared";

export default class AdaptiveCardFabric extends AC.AdaptiveCard {
    private static iconInitialized = false;

    constructor() {
        super();
        if (!AdaptiveCardFabric.iconInitialized) {
            initializeIcons();
            AdaptiveCardFabric.iconInitialized = true;
        }

        // add component extensions
        AdaptiveCardFabric.elementTypeRegistry.registerType("Input.Date", () => new Components.InputDateFabric());
        AdaptiveCardFabric.elementTypeRegistry.registerType("Input.Text", () => new Components.InputTextFabric());
        AdaptiveCardFabric.elementTypeRegistry.registerType("Input.Time", () => new Components.InputTimeFabric());
        AdaptiveCardFabric.elementTypeRegistry.registerType("Input.Number", () => new Components.InputNumberFabric());
        AdaptiveCardFabric.elementTypeRegistry.registerType("Input.Toggle", () => new Components.InputToggleFabric());
        AdaptiveCardFabric.elementTypeRegistry.registerType("Input.ChoiceSet", () => new Components.InputChoiceSetFabric());

        // add actions extensions
        AdaptiveCardFabric.actionTypeRegistry.registerType("Action.OpenUrl", () => new Actions.OpenUrlActionFabric());
        AdaptiveCardFabric.actionTypeRegistry.registerType("Action.Submit", () => new Actions.SubmitActionFabric());
        AdaptiveCardFabric.actionTypeRegistry.registerType("Action.ShowCard", () => new Actions.ShowCardActionFabric());
        AdaptiveCardFabric.actionTypeRegistry.registerType("Action.ToggleVisibility", () => new Actions.ToggleVisibilityActionFabric());
    }

    public render(target?: HTMLElement): HTMLElement {
        const card = super.render(target);
        const focusZone = (
            <FocusZone
                direction={FocusZoneDirection.horizontal}
                handleTabKey={FocusZoneTabbableElements.all}
                isCircularNavigation={true}
            >
                <div ref={(n) => n.appendChild(card)}></div>
            </FocusZone>);
        let cardWithFocus = getDiv();
        ReactDOM.render(focusZone, cardWithFocus);
        return cardWithFocus;
    }
}
