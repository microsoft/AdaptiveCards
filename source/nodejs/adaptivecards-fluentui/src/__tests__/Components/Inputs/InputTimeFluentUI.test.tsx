// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { InputTimeFluentUI } from "../../../components/inputs/InputTimeFluentUI";
import * as TestUtils from "../../TestUtils";
import { initializeIcons } from "@fluentui/react";

initializeIcons();

describe("InputTimeExtended", () => {
    it("should be rendered successfully", () => {
        let input = new InputTimeFluentUI();

        expect(input).toBeDefined();
        expect(input.render()).toBeDefined();
    });

    it("should render input time correctly", () => {
        let input = TestUtils.renderFluentComponent(InputTimeFluentUI, {
            "type": "Input.Time",
            "id": "time",
            "min": "09:00",
            "max": "17:00",
            "value": "15:30",
        });

        expect(input).toBeDefined();
        expect(input).toMatchSnapshot();
    });

    it("can get json name", () => {
        expect(new InputTimeFluentUI().getJsonTypeName()).toBe("Input.Time");
    });

    it("generates json correctly", () => {
        const element = new InputTimeFluentUI();
        element.parse({
            "type": "Input.Time",
            "id": "time",
            "min": "09:00",
            "max": "17:00",
            "value": "15:30",
        });

        const json = element.toJSON();
        expect(json).toBeDefined();
        expect(json.type).toEqual("Input.Time");
        expect(json.value).toEqual("15:30");
        expect(json.max).toEqual("17:00"); 
        expect(json.min).toEqual("09:00");

    });
});
