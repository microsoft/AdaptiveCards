// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as FabricUI from "office-ui-fabric-react";
import * as AC from "adaptivecards";
import * as Shared from "../../Utils/shared";

export class InputDateFabric extends Shared.ReactInputElement {
    public value: string;
    private date: Date;
    private placeholder: string;
    private minDate: Date;
    private maxDate: Date;

    protected renderReact = (): JSX.Element => {
        return this.buildDatePicker();
    }

    public getJsonTypeName = (): string => "Input.Date";

    public parse = (json: any, errors?: AC.IValidationError[]) => {
        this.id = AC.getStringValue(json.id);
        this.placeholder = AC.getStringValue(json.placeholder);
        this.parseDates(json, errors);
    }

    private parseDates = (json: any, errors?: AC.IValidationError[]) => {
        const dateString = AC.getStringValue(json.value);
        this.value = dateString;
        this.date = dateString ? this.getDate(dateString) : new Date();
        this.minDate = json.min ? this.getDate(AC.getStringValue(json.min)) : undefined;
        this.maxDate = json.max ? this.getDate(AC.getStringValue(json.max)) : undefined;
    }

    private getDate = (dateString: string, errors?: AC.IValidationError[]): Date => {
        try {
            return new Date(dateString);
        } catch (error) {
            Shared.raiseParseError({
                error: AC.ValidationError.InvalidPropertyValue,
                message: error,
            }, errors);
            return undefined;
        }
    }

    private buildDatePicker = () => {
        return (<FabricUI.DatePicker
            id={this.id}
            onSelectDate={this.handleSelectDate}
            value={this.date}
            placeholder={this.placeholder}
            allowTextInput={true}
            minDate={this.minDate}
            maxDate={this.maxDate}
        />);
    }

    private handleSelectDate = (date: Date) => {
        this.value = date.toLocaleDateString("en-US");
    }
}
