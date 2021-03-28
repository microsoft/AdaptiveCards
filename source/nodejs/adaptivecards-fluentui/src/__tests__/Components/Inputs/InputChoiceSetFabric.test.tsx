// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { renderFluentComponent } from "../../TestUtils";
import { InputChoiceSetFluentUI } from "../../../components/inputs/InputChoiceSetFluentUI";
import { initializeIcons } from "@fluentui/react";

initializeIcons();

const inputChoiceProps = [
    {
        "type": "Input.ChoiceSet",
        "title": "Red",
        "value": "1",
    },
    {
        "type": "Input.ChoiceSet",
        "title": "Green",
        "value": "2",
    },
    {
        "type": "Input.ChoiceSet",
        "title": "Blue",
        "value": "3",
    },
];
const inputChoiceSetComboBox = {
    "type": "Input.ChoiceSet",
    "isMultiSelect": false,
    "style": "compact",
    "value": "1",
    "choices": inputChoiceProps,
};
const inputChoiceSetChoiceGroup = {
    "type": "Input.ChoiceSet",
    "isMultiSelect": false,
    "style": "expanded",
    "value": "1",
    "choices": inputChoiceProps,
};
const inputChoiceSetComboBoxMultiSelect = {
    "type": "Input.ChoiceSet",
    "isMultiSelect": true,
    "style": "compact",
    "value": "1, 2",
    "choices": inputChoiceProps,
};
const inputChoiceSetCheckboxMultiSelect = {
    "type": "Input.ChoiceSet",
    "isMultiSelect": true,
    "style": "expanded",
    "value": "1,3",
    "choices": inputChoiceProps,
};

describe("InputChoiceSet", () => {
    it("inputChoiceSetComboBox should be rendered correctly", () => {
        let el = renderFluentComponent(InputChoiceSetFluentUI, inputChoiceSetComboBox);
        expect(el).toMatchSnapshot();
    });

    it("inputChoiceSetChoiceGroup should be rendered correctly", () => {
        let el = renderFluentComponent(InputChoiceSetFluentUI, inputChoiceSetChoiceGroup);
        expect(el).toMatchSnapshot();
    });

    it("inputChoiceSetComboBoxMultiSelect should be rendered correctly", () => {
        let el = renderFluentComponent(InputChoiceSetFluentUI, inputChoiceSetComboBoxMultiSelect);
        expect(el).toMatchSnapshot();
    });

    it("inputChoiceSetCheckboxMultiSelect should be rendered correctly", () => {
        let el = renderFluentComponent(InputChoiceSetFluentUI, inputChoiceSetCheckboxMultiSelect);
        expect(el).toMatchSnapshot();
    });

    it("can get json name", () => {
        expect(new InputChoiceSetFluentUI().getJsonTypeName()).toBe("Input.ChoiceSet");
    });

    it("generates json correctly", () => {
        const element = new InputChoiceSetFluentUI();
        element.parse(inputChoiceSetComboBox);

        const json = element.toJSON();
        expect(json).toBeDefined();
        expect(json.type).toEqual("Input.ChoiceSet");
        expect(json.value).toEqual("1");
        expect(json.choices).toBeDefined();
    });
});
