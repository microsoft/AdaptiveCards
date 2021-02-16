// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import {Image} from "../../card-elements";

test('Image should be instantiated', ()=>{
    const image = new Image();
    expect(image).toEqual(expect.anything());
    expect(image.altText).toBeUndefined();
})
