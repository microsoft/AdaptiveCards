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
    private style: AC.InputTextStyle = AC.InputTextStyle.Text;

    protected renderReact = (): JSX.Element => {
        return this.buildInput();
    }

    public getJsonTypeName = (): string => "Input.Text";

    public parse = (json: any, errors?: any) => {
        super.parse(json, errors);
        this.value = this.defaultValue;
        this.isMultiline = AC.getBoolValue(json.isMultiline, false);
        this.maxLength = Shared.getIntValue(json.maxLength);
        this.placeholder = AC.getStringValue(json.placeholder);
        this.label = AC.getStringValue(json.label);
        this.style = AC.getEnumValue(AC.InputTextStyle, json.style, AC.InputTextStyle.Text);
        this.inlineAction = AC.createActionInstance(this, json.inlineAction, [AC.ShowCardAction.JsonTypeName], false, errors);
    }

    public toJSON = () => {
        let result = super.toJSON();

        AC.setProperty(result, "placeholder", this.placeholder);
        AC.setProperty(result, "maxLength", this.maxLength, 0);
        AC.setProperty(result, "isMultiline", this.isMultiline, false);
        AC.setEnumProperty(AC.InputTextStyle, result, "style", this.style, AC.InputTextStyle.Text);
        if (this.inlineAction) {
            AC.setProperty(result, "inlineAction", this.inlineAction.toJSON());
        }

        return result;
    }

    private buildInput = (): JSX.Element => {
        return (
            <TextField
                id={this.id}
                type={AC.InputTextStyle[this.style].toLowerCase()}
                value={this.defaultValue}
                multiline={this.isMultiline}
                maxLength={this.maxLength}
                placeholder={this.placeholder}
                label={this.label}
                onChange={this.handleChange}
                onKeyDown={this.handleKeyDown}
            />
        );
    }

    private handleKeyDown = (e: React.KeyboardEvent<HTMLInputElement | HTMLTextAreaElement>): void => {
        // Enter pressed
        if (e.keyCode === 13 && this.inlineAction) {
            this.inlineAction.execute();
        }
    }
}
