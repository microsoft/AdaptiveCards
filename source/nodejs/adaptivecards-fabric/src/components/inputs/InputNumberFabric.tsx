// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as AC from "adaptivecards";
import * as FabricUI from "@fluentui/react";
import * as Shared from "../../utils/shared";

export class InputNumberFabric extends Shared.ReactInputElement {

    private max?: number;
    private min?: number;
    private placeholder: string;

    public parse = (json: any, errors?: AC.IValidationError[]) => {
        super.parse(json, errors);
        this.value = this.defaultValue;
        this.min = Shared.getIntValue(json.min);
        this.max = Shared.getIntValue(json.max);
        this.placeholder = AC.getStringValue(json.placeholder);
    }

    protected renderReact = (): JSX.Element => (
        <FabricUI.TextField
            id={this.id}
            placeholder={`${this.placeholder}`}
            value={`${this.defaultValue}`}
            type="number"
            max={this.max}
            min={this.min}
            onChange={this.handleChange}
        />
    )

    public getJsonTypeName = (): string => "Input.Number";

    public toJSON = () => {
        let result = super.toJSON();

        AC.setProperty(result, "placeholder", this.placeholder);
        AC.setProperty(result, "min", this.min);
        AC.setProperty(result, "max", this.max);

        return result;
    }
}
