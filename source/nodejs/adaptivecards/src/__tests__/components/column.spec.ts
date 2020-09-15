// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { BackgroundImage, Column } from "../../card-elements";

test('Column should be instantiated', () => {
    const column = new Column();
    expect(column).toEqual(expect.anything());
})

test('Column can have a backgroundImage set', () =>{
    const column = new Column();
    const background = new BackgroundImage();
    background.url = 'https://adaptivecards.io/content/outlook-logo.png'
    column.backgroundImage = background;

    expect(column.backgroundImage).not.toBeNull()
})
