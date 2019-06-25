// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import { TextField } from "office-ui-fabric-react";
import * as AC from "adaptivecards";
import * as Shared from "../../Utils/shared";

export class InputTextFabric extends Shared.ReactInputElement {
    public value: string;
    private isMultiline: boolean;
    private maxLength: number;
    private placeholder: string;
    private label: string;

    protected renderReact = (): JSX.Element => {
        return this.buildInput();
    }

    public getJsonTypeName = (): string => "Input.Text";

    public parse = (json: any, errors?: any) => {
        this.value = json.value;
        this.id = AC.getStringValue(json.id);
        this.isMultiline = AC.getBoolValue(json.isMultiline, false);
        this.maxLength = Shared.getIntValue(json.maxLength);
        this.placeholder = AC.getStringValue(json.placeholder);
        this.label = AC.getStringValue(json.label);
    }

    private buildInput = (): JSX.Element => {
        return (
            <TextField
                id={this.id}
                value={this.value}
                multiline={this.isMultiline}
                maxLength={this.maxLength}
                placeholder={this.placeholder}
                label={this.label}
                onChange={this.handleChange}
            />
        );
    }
}
