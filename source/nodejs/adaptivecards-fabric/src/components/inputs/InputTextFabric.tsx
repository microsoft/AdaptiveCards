// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import { TextField } from "office-ui-fabric-react";
import * as AC from "adaptivecards";
import * as Shared from "../../utils/shared";

export class InputTextFabric extends Shared.ReactInputElement {

    private isMultiline: boolean;
    private maxLength: number;
    private placeholder: string;
    private label: string;

    protected renderReact = (): JSX.Element => {
        return this.buildInput();
    }

    public getJsonTypeName = (): string => "Input.Text";

    public parse = (json: any, errors?: any) => {
        super.parse(json, errors);
        this.value = json.value;
        this.isMultiline = AC.getBoolValue(json.isMultiline, false);
        this.maxLength = Shared.getIntValue(json.maxLength);
        this.placeholder = AC.getStringValue(json.placeholder);
        this.label = AC.getStringValue(json.label);
    }

    public toJSON = () => {
        let result = super.toJSON();

        AC.setProperty(result, "placeholder", this.placeholder);
        AC.setProperty(result, "maxLength", this.maxLength, 0);
        AC.setProperty(result, "isMultiline", this.isMultiline, false);

        return result;
    }

    private buildInput = (): JSX.Element => {
        return (
            <TextField
                id={this.id}
                value={this.defaultValue}
                multiline={this.isMultiline}
                maxLength={this.maxLength}
                placeholder={this.placeholder}
                label={this.label}
                onChange={this.handleChange}
            />
        );
    }
}
