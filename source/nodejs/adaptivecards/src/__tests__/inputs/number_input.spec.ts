// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { NumberInput } from "../../card-elements";

test("NumberInput should be instantiated", () => {
    const numberInput = new NumberInput();
    expect(numberInput).toEqual(expect.anything());
});

describe("NumberInput with min and max left empty", () => {
    function createEmptyNumberInput(isRequired: boolean): NumberInput {
        const numberInput = new NumberInput();
        numberInput.min = 1;
        numberInput.max = 10;
        numberInput.isRequired = isRequired;

        // An empty rendered <input type="number"> reports NaN through valueAsNumber
        Object.defineProperty(numberInput, "value", { get: () => NaN });

        return numberInput;
    }

    test("is valid when optional", () => {
        const numberInput = createEmptyNumberInput(false);

        expect(numberInput.isValid()).toBe(true);
        expect(numberInput.validateValue()).toBe(true);
    });

    test("is invalid when required", () => {
        const numberInput = createEmptyNumberInput(true);

        expect(numberInput.isValid()).toBe(false);
        expect(numberInput.validateValue()).toBe(false);
    });
});
