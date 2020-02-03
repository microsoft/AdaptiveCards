// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import {DateInput} from "../../card-elements";

test('DateInput should be instantiated', ()=>{
    const dateInput = new DateInput();
    expect(dateInput).toEqual(expect.anything());
})
