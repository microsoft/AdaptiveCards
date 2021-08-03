// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { InputToggleFabric } from "../../../components/inputs/InputToggleFabric";
import { renderFabricComponent } from "../../TestUtils";
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
        let el = renderFabricComponent(InputToggleFabric, toggleProps);

        expect(el).toMatchSnapshot();
    });

    it("can set initial value", () => {
        let el = renderFabricComponent(InputToggleFabric, toggleProps);

        expect(el.querySelector("button").getAttribute("aria-checked")).toBe("true");
    });

    it("can get json name", () => {
        expect(new InputToggleFabric().getJsonTypeName()).toBe("Input.Toggle");
    });

    it("generates json correctly", () => {
        const element = new InputToggleFabric();
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
