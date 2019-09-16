// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { ShowCardAction } from "../../card-elements";

test('ShowCardAction should be instantiated', () => {
    const showCardAction = new ShowCardAction();
    expect(showCardAction).toEqual(expect.anything());
})
