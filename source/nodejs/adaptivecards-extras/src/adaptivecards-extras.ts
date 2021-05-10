// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { ProgressBar } from "./progress-bar";

export * from "./progress-bar";

export function registerAllFeatures(elementsRegistry?: Adaptive.CardObjectRegistry<Adaptive.CardElement>, actionsRegistry?: Adaptive.CardObjectRegistry<Adaptive.Action>) {
    let targetElementRegistry = elementsRegistry ? elementsRegistry : Adaptive.GlobalRegistry.elements;

    targetElementRegistry.register("Extras.ProgressBar", ProgressBar, Adaptive.Versions.v1_0);
}