// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { AdaptiveCard } from "../../card-elements";

test('AdaptiveCard should be instantiated', () => {
    const adaptiveCard = new AdaptiveCard();
    expect(adaptiveCard).toEqual(expect.anything());
})
