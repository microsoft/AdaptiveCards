// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { InputToggleFabric } from "../../../Components/Inputs/InputToggleFabric";
import { renderFabricComponent } from "../../TestUtils";
import { initializeIcons } from "office-ui-fabric-react";

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
});
