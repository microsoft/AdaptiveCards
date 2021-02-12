// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { OverflowAction, Action } from "../../card-elements";

test('OverflowAction should be instantiated', () => {
    const actions: Action[] = [];
    const actionSet = new OverflowAction(actions);
    expect(actionSet).toEqual(expect.anything());
})
