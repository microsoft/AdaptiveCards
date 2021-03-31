// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { AdaptiveCard, TextInput, SerializationContext } from "../../card-elements";
import { Versions } from "../../serialization";

test('TextInput should be instantiated', ()=>{
    const textInput = new TextInput();
    expect(textInput).toEqual(expect.anything());
})

test('TextInput should be able to roundtrip', ()=>{
    const sample_card = {
        "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
        "type":"AdaptiveCard",
        "body":[
            {
                "type":"Input.Text",
                "id":"test-url",
                "style":"Url"
            },
            {
                "type":"Input.Text",
                "id":"test-email",
                "style":"Email",
                "horizontalAlignment": "Center"
            },
            {
                "type":"Input.Text",
                "id":"test-unspecified"
            }

            ],
        "version":"1.0"
    };
    let ac : AdaptiveCard = new AdaptiveCard();
    ac.parse(sample_card);
    let json = ac.toJSON(new SerializationContext(Versions.v1_0));
    expect(sample_card).toEqual(json);
})
