/**
 * @jest-environment jsdom
 */
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { replaceTextHighlightMarkers } from "../../utils";

const openingTag = '<mark style="background-color: #FFFF00;">';
const closingTag = "</mark>";

function highlight(html: string): DocumentFragment {
    const template = document.createElement("template");
    template.innerHTML = replaceTextHighlightMarkers(html, openingTag, closingTag);

    return template.content;
}

function markTexts(fragment: DocumentFragment): string[] {
    return Array.from(fragment.querySelectorAll("mark")).map((mark) => mark.textContent ?? "");
}

describe("TextBlock text highlighting markers", () => {
    test("are replaced in text content, including across inline elements", () => {
        expect(
            replaceTextHighlightMarkers(
                "<p>a ===b/==/ c ===<strong>d</strong>/==/</p>",
                openingTag,
                closingTag
            )
        ).toEqual(`<p>a ${openingTag}b</mark> c ${openingTag}<strong>d</strong></mark></p>`);
    });

    test("leave HTML without markers unchanged", () => {
        const html = "<p><a href='https://e.example/'>x</a><br/></p>";

        expect(replaceTextHighlightMarkers(html, openingTag, closingTag)).toBe(html);
    });

    test("are left untouched inside attribute values", () => {
        const fragment = highlight(
            '<p><a href="https://e.example/a===b/==/c" title="t===<img src=x>">x===y/==/</a>' +
                "<img src='https://e.example/x===y.png' alt=\"i>===\"></p>"
        );

        expect(markTexts(fragment)).toEqual(["y"]);
        expect(fragment.querySelector("a")?.getAttribute("href")).toBe(
            "https://e.example/a===b/==/c"
        );
        expect(fragment.querySelector("a")?.getAttribute("title")).toBe("t===<img src=x>");
        expect(fragment.querySelectorAll("img")).toHaveLength(1);
        expect(fragment.querySelector("img")?.getAttribute("alt")).toBe("i>===");
    });

    test("are left untouched inside attributes that follow a comment containing a quote", () => {
        const fragment = highlight(
            '<p><!-- " --><a title=">===<img src=x onerror=alert(1)>">link</a></p>'
        );

        expect(fragment.querySelector("mark")).toBeNull();
        expect(fragment.querySelectorAll("img")).toHaveLength(0);
        expect(fragment.querySelector("a")?.getAttribute("title")).toBe(
            ">===<img src=x onerror=alert(1)>"
        );
    });

    test("are left untouched inside raw-text elements and in attributes that follow them", () => {
        const fragment = highlight(
            '<p>a<style>p{}<"===</style><a title=">===<img src=x onerror=alert(1)>">l</a>' +
                "<textarea>===t/==/</textarea></p>"
        );

        expect(fragment.querySelector("mark")).toBeNull();
        expect(fragment.querySelectorAll("img")).toHaveLength(0);
        expect(fragment.querySelector("style")?.textContent).toBe('p{}<"===');
        expect(fragment.querySelector("textarea")?.value).toBe("===t/==/");
    });

    test("are left untouched inside svg and CDATA content", () => {
        const fragment = highlight(
            '<p><svg><style><a title="</style>===<img src=x onerror=alert(1)>"></a></style>' +
                '<![CDATA[ x" ]]><a title=">===<img src=x onerror=alert(1)>"></a></svg></p>'
        );

        expect(fragment.querySelector("mark")).toBeNull();
        expect(fragment.querySelectorAll("img")).toHaveLength(0);
    });

    test("are left untouched inside attributes whose name contains a quote", () => {
        const fragment = highlight('<p><a x"=">===<img src=x onerror=alert(1)>">l</a></p>');

        expect(fragment.querySelector("mark")).toBeNull();
        expect(fragment.querySelectorAll("img")).toHaveLength(0);
    });

    test("after a comment containing a quote are still replaced in text content", () => {
        expect(markTexts(highlight("<p><!-- ' -->a===b/==/c'</p>"))).toEqual(["b"]);
    });

    test("pass the HTML through the given Trusted Types conversion before parsing", () => {
        const converted: string[] = [];

        replaceTextHighlightMarkers("<p>===a/==/</p>", openingTag, closingTag, (value) => {
            converted.push(value);
            return value;
        });

        expect(converted).toEqual(["<p>===a/==/</p>"]);
    });
});
