// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import {NumberInput} from "../../card-elements";

test('NumberInput should be instantiated', ()=>{
    const numberInput = new NumberInput();
    expect(numberInput).toEqual(expect.anything());
})
