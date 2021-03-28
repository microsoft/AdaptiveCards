// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { InputToggleFluentUI } from "../../../components/inputs/InputToggleFluentUI";
import { renderFluentComponent } from "../../TestUtils";
import { initializeIcons } from "@fluentui/react";

initializeIcons();

const toggleProps = {
    type: "Input.Toggle",
    title: "Are you sure?",
    value: "yeah",
    valueOn: "yeah",
    valueOff: "nope",
};

describe("InputToggleExtended", () => {
    it("should be rendered correctly", () => {
        let el = renderFluentComponent(InputToggleFluentUI, toggleProps);

        expect(el).toMatchSnapshot();
    });

    it("can set initial value", () => {
        let el = renderFluentComponent(InputToggleFluentUI, toggleProps);

        expect(el.querySelector("button").getAttribute("aria-checked")).toBe("true");
    });

    it("can get json name", () => {
        expect(new InputToggleFluentUI().getJsonTypeName()).toBe("Input.Toggle");
    });

    it("generates json correctly", () => {
        const element = new InputToggleFluentUI();
        element.parse(toggleProps);

        const json = element.toJSON();
        expect(json).toBeDefined();
        expect(json.type).toEqual("Input.Toggle");
        expect(json.title).toEqual("Are you sure?");
        expect(json.value).toEqual("yeah");
        expect(json.valueOn).toEqual("yeah");
        expect(json.valueOff).toEqual("nope");
    });
});
