// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Column } from "../../card-elements";

test('Column should be instantiated', () => {
    const column = new Column();
    expect(column).toEqual(expect.anything());
})
