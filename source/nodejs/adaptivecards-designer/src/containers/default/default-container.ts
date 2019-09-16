// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { HostContainer } from "../host-container";

export class DefaultContainer extends HostContainer {
    public renderTo(hostElement: HTMLElement) {
        hostElement.classList.add("card-frame");
        hostElement.appendChild(this.cardHost);
    }
}
