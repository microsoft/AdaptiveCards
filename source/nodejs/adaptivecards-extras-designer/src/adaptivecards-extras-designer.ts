// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { CardDesignerSurface } from "adaptivecards-designer";
import { ProgressBar } from "@microsoft/adaptivecards-extras";
import { ProgressBarPeer } from "./progress-bar-designer";

export * from "./progress-bar-designer";

export function initializeDesignerSupport() {
    CardDesignerSurface.cardElementPeerRegistry.registerPeer(ProgressBar, ProgressBarPeer, "Extras");
}
