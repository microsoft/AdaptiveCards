// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import {ImageSetConfig} from "../../host-config";

test('ImageSetConfig should parse valid json', ()=>{
    const imageSizeJson = {
        imageSize: 10,
        maxImageHeight: 50
    }
    const imageSetConfig = new ImageSetConfig(imageSizeJson);

    expect(imageSetConfig.imageSize).toEqual(10);
    expect(imageSetConfig.maxImageHeight).toEqual(50);
})
