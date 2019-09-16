// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import {FactSet} from "../../card-elements";

test('FactSet should be instantiated', ()=>{
    const factSet = new FactSet();
    expect(factSet).toEqual(expect.anything());
})
