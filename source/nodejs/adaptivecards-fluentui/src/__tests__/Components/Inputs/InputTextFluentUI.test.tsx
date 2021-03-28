// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { InputTextFluentUI } from "../../../components/inputs/InputTextFluentUI";
import * as TestUtils from "../../TestUtils";
import { initializeIcons } from "@fluentui/react";

initializeIcons();

describe("InputTextExtended", () => {
    it("should be rendered successfully", () => {
        let input = new InputTextFluentUI();

        expect(input).toBeDefined();
        expect(input.render()).toBeDefined();
    });

    it("renders int text multiline correctly", () => {
        let input = TestUtils.renderFluentComponent(InputTextFluentUI, {
            "type": "Input.Text",
            "id": "input3",
            "placeholder": "enter comment",
            "maxLength": 500,
            "isMultiline": true,
            "value": "This value was pre-filled",
        });

        expect(input).toMatchSnapshot();
    });

    it("renders int text single line correctly", () => {
        let input = TestUtils.renderFluentComponent(InputTextFluentUI, {
            "type": "Input.Text",
            "id": "input3",
            "placeholder": "enter comment",
            "maxLength": 500,
            "isMultiline": false,
            "value": "This value was pre-filled",
        });

        expect(input).toMatchSnapshot();
    });

    it("can serialize inline action", () => {
        let input = new InputTextFluentUI();
        input.parse({
            "type": "Input.Text",
            "id": "input1",
            "inlineAction": {
                "type": "Action.Submit",
                "iconUrl": "http://adaptivecards.io/content/cats/1.png",
                "title": "Reply",
            },
        });

        let json = input.toJSON();

        expect(json).toBeDefined();
        expect(json.inlineAction).toBeDefined();
    });

    it("renders text box with inline action correctly", () => {
        let input = TestUtils.renderFluentComponent(InputTextFluentUI, {
            "type": "Input.Text",
            "id": "input3",
            "placeholder": "enter comment",
            "maxLength": 500,
            "isMultiline": false,
            "value": "This value was pre-filled",
        });

        expect(input).toMatchSnapshot();
    });

    it("can set initial value", () => {
        let el = TestUtils.renderFluentComponent(InputTextFluentUI, {
            "type": "Input.Text",
            "id": "input3",
            "placeholder": "enter comment",
            "maxLength": 500,
            "value": "This value was pre-filled",
        });

        expect(el).toBeDefined();
        let inputElement = el.querySelector("input");
        expect(inputElement).not.toBe(null);
        expect(inputElement.getAttribute("value")).toBe("This value was pre-filled");
    });

    it("can render placeholder", () => {
        let el = TestUtils.renderFluentComponent(InputTextFluentUI, {
            "type": "Input.Text",
            "id": "blah",
            "placeholder": "enter comment",
        });

        expect(el).toBeDefined();
        let inputElement = el.querySelector("input");
        expect(inputElement).not.toBe(null);
        expect(inputElement.getAttribute("placeholder")).toBe("enter comment");
    });

    it("can get json name", () => {
        expect(new InputTextFluentUI().getJsonTypeName()).toBe("Input.Text");
    });

    it("generates json correctly", () => {
        const element = new InputTextFluentUI();
        element.parse({
            "type": "Input.Text",
            "id": "blah",
            "placeholder": "enter comment",
            "style": "url"
        });

        const json = element.toJSON();
        expect(json).toBeDefined();
        expect(json.type).toEqual("Input.Text");
        expect(json.placeholder).toEqual("enter comment");
        expect(json.style).toEqual("Url");
    });
});
