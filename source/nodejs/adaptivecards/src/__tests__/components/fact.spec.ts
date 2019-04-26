// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import {Fact} from "../../card-elements";

test('Fact should be instantiated', ()=>{
    const fact = new Fact();
    expect(fact).toEqual(expect.anything());
})
