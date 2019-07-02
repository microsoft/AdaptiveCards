// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as AC from "adaptivecards";
import * as FabricUI from "office-ui-fabric-react";
import * as Shared from "../../utils/shared";

export class InputTimeFabric extends Shared.ReactInputElement {
    
    private placeholder: string;
    private min: string;
    private max: string;

    public parse = (json: any, errors?: AC.IValidationError[]) => {
        this.id = AC.getStringValue(json.id);
        this.valueInternal = json.value;
        this.placeholder = AC.getStringValue(json.placeholder);
        this.min = AC.getStringValue(json.min);
        this.max = AC.getStringValue(json.max);
    }

    protected renderReact = (): JSX.Element => {
        return (
            <FabricUI.TextField
                id={this.id}
                placeholder={`${this.placeholder}`}
                value={`${this.value}`}
                type="time"
                onChange={this.handleChange}
                max={this.max}
                min={this.min}
            />
        );
    }

    public getJsonTypeName = (): string => "Input.Time";
}
