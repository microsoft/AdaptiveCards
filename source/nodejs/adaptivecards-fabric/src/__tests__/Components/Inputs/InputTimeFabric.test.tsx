// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { InputTimeFabric } from "../../../Components/Inputs/InputTimeFabric";
import * as TestUtils from "../../TestUtils";
import { initializeIcons } from "office-ui-fabric-react";

initializeIcons();

describe("InputTimeExtended", () => {
    it("should be rendered successfully", () => {
        let input = new InputTimeFabric();

        expect(input).toBeDefined();
        expect(input.render()).toBeDefined();
    });

    it("should render input time correctly", () => {
        let input = TestUtils.renderFabricComponent(InputTimeFabric, {
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
        expect(new InputTimeFabric().getJsonTypeName()).toBe("Input.Time");
    });
});
