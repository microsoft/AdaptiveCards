// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { AdaptiveCard, TextBlock } from "../../card-elements";
import { replaceTextHighlightMarkers } from "../../utils";

test("TextBlock should be instantiated", () => {
    const textBlock = new TextBlock();
    expect(textBlock).toEqual(expect.anything());
});

describe("TextBlock text highlighting markers", () => {
    const openingTag = '<mark style="background-color: #FFFF00;">';

    test("are replaced in text content, including across inline elements", () => {
        expect(
            replaceTextHighlightMarkers(
                "<p>a ===b/==/ c ===<strong>d</strong>/==/</p>",
                openingTag,
                "</mark>"
            )
        ).toEqual(
            `<p>a ${openingTag}b</mark> c ${openingTag}<strong>d</strong></mark></p>`
        );
    });

    test("are left untouched inside attribute values", () => {
        const html =
            '<p><a href="https://e.example/a===b/==/c" title="t===<img src=x>">x===y/==/</a>' +
            "<img src='https://e.example/x===y.png' alt=\"i>===\"></p>";

        expect(replaceTextHighlightMarkers(html, openingTag, "</mark>")).toEqual(
            '<p><a href="https://e.example/a===b/==/c" title="t===<img src=x>">' +
                `x${openingTag}y</mark></a>` +
                "<img src='https://e.example/x===y.png' alt=\"i>===\"></p>"
        );
    });
});

const emoji_message = "Mix 🗣 emoji inside 🙌 text";
const simple_test_card = {
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "TextBlock",
            "text": emoji_message
        }
    ]
};

// TODO: confirm this test working as expected
// test('TextBlock should allow for Unicode chars including Emoji', ()=>{
//     const ac = new AdaptiveCard();
//     ac.parse(simple_test_card);
//     const result = ac.render();
//     const text = result.textContent.trim();
//     expect(text).toEqual(emoji_message);
// });
