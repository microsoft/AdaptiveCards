// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { HttpAction } from "../../card-elements";

test('HttpAction should be instantiate', () => {
    const httpAction = new HttpAction();
    expect(httpAction).toEqual(expect.anything());
})
