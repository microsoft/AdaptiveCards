// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import {TimeInput} from "../../card-elements";

test('TimeInput should be instantiated', ()=>{
    const timeInput = new TimeInput();
    expect(timeInput).toEqual(expect.anything());
})
