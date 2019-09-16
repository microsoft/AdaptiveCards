// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import {OpenUrlAction} from "../../card-elements";

test('OpenUrlAction should be instantiated', ()=>{
    const openUrlAction = new OpenUrlAction();
    expect(openUrlAction).toEqual(expect.anything());
})
