// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { CardElement } from "adaptivecards";

export const renderFabricComponent = <T extends CardElement>(type: { new(): T; }, json: any): HTMLElement => {
    let el = new type();
    el.parse(json);
    return el.render();
};
