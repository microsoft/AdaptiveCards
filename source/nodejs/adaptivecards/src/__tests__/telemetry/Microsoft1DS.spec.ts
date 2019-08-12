// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Microsoft1DSLogger } from "../../logging/Microsoft1DSLogger/Microsoft1DSLogger";

test('Microsoft1DSLogger should be instantiated', () => {
    const logger = new Microsoft1DSLogger();
    expect(logger).toEqual(expect.anything());
})
