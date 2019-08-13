// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import {ChoiceSetInput} from "../../card-elements";

test('ChoiceSetInput should be instantiated', ()=>{
    const choiceSetInput = new ChoiceSetInput();
    expect(choiceSetInput).toEqual(expect.anything());
})
