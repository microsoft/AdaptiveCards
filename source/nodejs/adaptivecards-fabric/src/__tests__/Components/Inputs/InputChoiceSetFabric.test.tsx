// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { renderExtendedComponent } from "../../TestUtils";
import { InputChoiceSetFabric } from "../../../Components/Inputs/InputChoiceSetFabric";
import { initializeIcons } from "office-ui-fabric-react";

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
        let el = renderExtendedComponent(InputChoiceSetFabric, inputChoiceSetComboBox);
        expect(el).toMatchSnapshot();
    });

    it("inputChoiceSetChoiceGroup should be rendered correctly", () => {
        let el = renderExtendedComponent(InputChoiceSetFabric, inputChoiceSetChoiceGroup);
        expect(el).toMatchSnapshot();
    });

    it("inputChoiceSetComboBoxMultiSelect should be rendered correctly", () => {
        let el = renderExtendedComponent(InputChoiceSetFabric, inputChoiceSetComboBoxMultiSelect);
        expect(el).toMatchSnapshot();
    });

    it("inputChoiceSetCheckboxMultiSelect should be rendered correctly", () => {
        let el = renderExtendedComponent(InputChoiceSetFabric, inputChoiceSetCheckboxMultiSelect);
        expect(el).toMatchSnapshot();
    });

    it("can get json name", () => {
        expect(new InputChoiceSetFabric().getJsonTypeName()).toBe("Input.ChoiceSet");
    });
});
