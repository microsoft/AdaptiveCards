// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as AC from "adaptivecards";
import { initializeIcons } from "office-ui-fabric-react";
import * as Components from ".";
import * as Actions from "../actions";

let iconsInitialized = false;

export const useFabricComponents = () => {
    if (!iconsInitialized) {
        initializeIcons();
        iconsInitialized = true;
    }

    // add component extensions
    AC.AdaptiveCard.elementTypeRegistry.registerType("Input.Date", () => new Components.InputDateFabric());
    AC.AdaptiveCard.elementTypeRegistry.registerType("Input.Text", () => new Components.InputTextFabric());
    AC.AdaptiveCard.elementTypeRegistry.registerType("Input.Time", () => new Components.InputTimeFabric());
    AC.AdaptiveCard.elementTypeRegistry.registerType("Input.Number", () => new Components.InputNumberFabric());
    AC.AdaptiveCard.elementTypeRegistry.registerType("Input.Toggle", () => new Components.InputToggleFabric());
    AC.AdaptiveCard.elementTypeRegistry.registerType("Input.ChoiceSet", () => new Components.InputChoiceSetFabric());

    // add actions extensions
    AC.AdaptiveCard.actionTypeRegistry.registerType("Action.OpenUrl", () => new Actions.OpenUrlActionFabric());
    AC.AdaptiveCard.actionTypeRegistry.registerType("Action.Submit", () => new Actions.SubmitActionFabric());
    AC.AdaptiveCard.actionTypeRegistry.registerType("Action.ShowCard", () => new Actions.ShowCardActionFabric());
    AC.AdaptiveCard.actionTypeRegistry.registerType("Action.ToggleVisibility", () => new Actions.ToggleVisibilityActionFabric());
};
