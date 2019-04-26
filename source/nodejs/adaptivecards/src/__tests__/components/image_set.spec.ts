// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import {ImageSet} from "../../card-elements";

test('ImageSet should be instantiated', ()=>{
    const imageSet = new ImageSet();
    expect(imageSet).toEqual(expect.anything());
})
