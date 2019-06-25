// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as AC from "adaptivecards";
import * as FabricUI from "office-ui-fabric-react";
import * as Shared from "../../Utils/shared";

interface InputChoiceProps {
    type?: string;
    title: string;
    value: string;
}

export class InputChoiceSetFabric extends Shared.ReactInputElement {

    private isMultiSelect: boolean;
    private choices: InputChoiceProps[];
    private style: string;
    private selectedValues: string[] = [];

    public parse = (json: any, errors?: AC.IValidationError[]) => {
        this.id = json.id ? AC.getStringValue(json.id) : null;
        this.value = json.value;
        this.selectedValues = this.defaultValueToArray(this.value);
        this.choices = json.choices;
        this.isMultiSelect = AC.getBoolValue(json.isMultiSelect, false);
        this.title = AC.getStringValue(json.title);
        this.style = AC.getStringValue(json.style);
    }

    protected renderReact = (): JSX.Element => (
        this.style === "compact" ?
            <this.ComboBox /> :
            this.createExpandedView()
    )

    public getJsonTypeName = (): string => "Input.ChoiceSet";

    private ComboBox = (): JSX.Element => (
        <FabricUI.ComboBox
            onChange={this.handleComboBoxChange}
            id={this.id}
            options={this.inputChoicesToComboBoxOptions(this.choices)}
            multiSelect={this.isMultiSelect}
            selectedKey={this.defaultValueToArray(this.value)}
        />
    )

    private createExpandedView = (): JSX.Element => {
        return this.isMultiSelect ?
            this.inputChoicesToCheckbox() :
            this.createChoiceGroup();
    }

    private createChoiceGroup = (): JSX.Element => (
        <FabricUI.ChoiceGroup
            id={this.id}
            onChange={this.handleChoiceGroupChange}
            options={this.inputChoicesToChoiceGroupOptions(
                this.choices,
                this.defaultValueToArray(this.value))}
            multiple={this.isMultiSelect}
        />
    )

    private inputChoicesToCheckbox = (): JSX.Element => (
        <React.Fragment>
            {this.choices.map((c, i) =>
                <FabricUI.Checkbox
                    key={c.value}
                    label={c.title}
                    defaultChecked={this.defaultValueToArray(this.value).includes(c.value)}
                    onChange={(ev, checked) => {
                        this.updateMultiselectData(checked, c.value);
                        ev.stopPropagation();
                        ev.preventDefault();
                    }}
                    styles={{
                        root: {
                            paddingTop: i > 0 ? this.hostConfig.spacing.default : 0,
                        },
                    }}
                />,
            )}
        </React.Fragment>
    )

    private defaultValueToArray = (value: string): string[] => {
        if (value) {
            return value.split(",");
        }
        return [];
    }

    private inputChoicesToComboBoxOptions = (choices: InputChoiceProps[]): FabricUI.IComboBoxOption[] => {
        return choices.map<FabricUI.IComboBoxOption>(c => ({ key: c.value, text: c.title }));
    }

    private inputChoicesToChoiceGroupOptions = (choices: InputChoiceProps[], value: string[]): FabricUI.IChoiceGroupOption[] => {
        return choices.map<FabricUI.IChoiceGroupOption>(c => ({ key: c.value, text: c.title, checked: value.includes(c.value) }));
    }

    private handleChoiceGroupChange =
        (ev?: React.FormEvent<HTMLElement | HTMLInputElement>, option?: FabricUI.IChoiceGroupOption): void => {
            this.value = option.key;
            ev.stopPropagation();
            ev.preventDefault();
        }

    private handleComboBoxChange =
        (event: React.FormEvent<FabricUI.IComboBox>, option?: FabricUI.IComboBoxOption, index?: number, value?: string): void => {
            if (this.isMultiSelect) {
                this.updateMultiselectData(option.selected, option.key);
            } else {
                this.value = option.key;
            }
            event.stopPropagation();
            event.preventDefault();
        }

    private updateMultiselectData = (selected: boolean, key: any): void => {
        this.updateSelectedValues(selected, key);
        this.value = this.selectedValues.join(",");
    }

    private updateSelectedValues = (selected: boolean, key: any): void => {
        selected ? this.selectedValues.push(key) : this.removeItemFromArray(this.selectedValues, key);
    }

    private removeItemFromArray = (arr: any[], item: any): void => {
        const index = arr.indexOf(item);
        arr.splice(index, 1);
    }
}
