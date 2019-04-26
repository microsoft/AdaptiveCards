// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { ColumnSet } from "../../card-elements";

test('Container should be instantiated', () => {
    const columnSet = new ColumnSet();
    expect(columnSet).toEqual(expect.anything());
})
