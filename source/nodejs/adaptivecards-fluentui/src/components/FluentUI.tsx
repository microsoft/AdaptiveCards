// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as AC from "adaptivecards";
import { initializeIcons } from "@fluentui/react";
import * as Components from ".";
import * as Actions from "../actions";

let iconsInitialized = false;

export const useFluentUI = () => {
    if (!iconsInitialized) {
        initializeIcons();
        iconsInitialized = true;
    }

    // add component extensions
	AC.GlobalRegistry.elements.register("Input.Date", Components.InputDateFluentUI);
    AC.GlobalRegistry.elements.register("Input.Text", Components.InputTextFluentUI);
    AC.GlobalRegistry.elements.register("Input.Time", Components.InputTimeFluentUI);
	AC.GlobalRegistry.elements.register("Input.Number", Components.InputNumberFabric);
	AC.GlobalRegistry.elements.register("Input.Toggle",  Components.InputToggleFluentUI);
    AC.GlobalRegistry.elements.register("Input.ChoiceSet", Components.InputChoiceSetFluentUI);

    // add actions extensions
     AC.GlobalRegistry.actions.register("Action.OpenUrl", Actions.OpenUrlActionFluentUI);
	 AC.GlobalRegistry.actions.register("Action.Submit", Actions.SubmitActionFluentUI);
	 AC.GlobalRegistry.actions.register("Action.ShowCard", Actions.ShowCardActionFluentUI);
	 AC.GlobalRegistry.actions.register("Action.ToggleVisibility", Actions.ToggleVisibilityActionFluentUI);
	 AC.GlobalRegistry.actions.register("Action.Execute", Actions.SubmitActionFluentUI);
};
