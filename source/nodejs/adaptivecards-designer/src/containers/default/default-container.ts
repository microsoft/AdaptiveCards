// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { SingleThemeHostContainer } from "../single-theme-host-container";

export class DefaultContainer extends SingleThemeHostContainer {
    public renderTo(hostElement: HTMLElement) {
        hostElement.classList.add("card-frame");
        hostElement.appendChild(this.cardHost);
    }
}
