// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { InputDateFabric } from "../../../Components/Inputs/InputDateFabric";
import { initializeIcons } from "@uifabric/icons";
import * as TestUtils from "../../TestUtils";

initializeIcons();

describe("InputDateExtended", () => {
    it("should be rendered successfully", () => {
        let input = new InputDateFabric();

        expect(input).toBeDefined();
        expect(input.render()).toBeDefined();
    });

    it("renders component correctly", () => {
        let input = TestUtils.renderFabricComponent(InputDateFabric, {
            type: "Input.Date",
            id: "date",
            spacing: "none",
            value: "5/14/2019",
            placeholder: "Enter a date",
            max: "1/1/2020",
            min: "1/1/2010",
        });

        expect(input).toMatchSnapshot();
    });

    it("can get json name", () => {
        expect(new InputDateFabric().getJsonTypeName()).toBe("Input.Date");
    });
});
