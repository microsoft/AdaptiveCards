// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as AC from "adaptivecards";
import * as FluentUI from "@fluentui/react";
import * as Shared from "../../utils/shared";

export class InputChoiceSetFluentUI extends AC.ChoiceSetInput {

	private _value;
	public get value(): any {
	  return this._value || this.defaultValue;
	}
  
	public isSet(): any {
	  return this._value !== undefined || this.defaultValue !== undefined;
	}

	private _selectedValues: string[] = [];

	
	protected internalRender(): HTMLElement {
        const element = Shared.sharedInternalRender(this.renderReact);
        element.style.width = "100%";
        return element;
    }


    protected renderReact = (): JSX.Element => (
        this.isCompact ?
            <this.ComboBox /> :
            this.createExpandedView()
    )

    private parseChoises = (json: any) => {
        this.choices = Array.isArray(json.choices) ?
            json.choices.map(ch => {
                let choice = new AC.Choice();
                choice.parse(ch);
                return choice;
            }) :
            [];
    }

    private ComboBox = (): JSX.Element => (
        <FluentUI.ComboBox
            onChange={this.handleComboBoxChange}
            id={this.id}
            options={this.inputChoicesToComboBoxOptions(this.choices)}
            multiSelect={this.isMultiSelect}
			defaultSelectedKey={this.defaultValue}
			defaultValue={this.defaultValue}
			multiSelectDelimiter=","
            selectedKey={this._value}
        />
    )

    private createExpandedView = (): JSX.Element => {
        return this.isMultiSelect ?
            this.inputChoicesToCheckbox() :
            this.createChoiceGroup();
    }

    private createChoiceGroup = (): JSX.Element => (
        <FluentUI.ChoiceGroup
            id={this.id}
            onChange={this.handleChoiceGroupChange}
            options={this.inputChoicesToChoiceGroupOptions(
                this.choices,
                this.defaultValueToArray(this.defaultValue))}
            multiple={this.isMultiSelect}
        />
    )

    private inputChoicesToCheckbox = (): JSX.Element => (
        <React.Fragment>
            {this.choices.map((c, i) =>
                <FluentUI.Checkbox
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

    private inputChoicesToComboBoxOptions = (choices: AC.Choice[]): FluentUI.IComboBoxOption[] => {
        return choices.map<FluentUI.IComboBoxOption>(c => ({ key: c.value, text: c.title }));
    }

    private inputChoicesToChoiceGroupOptions = (choices: AC.Choice[], value: string[]): FluentUI.IChoiceGroupOption[] => {
        return choices.map<FluentUI.IChoiceGroupOption>(c => ({ key: c.value, text: c.title, checked: value.includes(c.value) }));
    }

    private handleChoiceGroupChange =
        (ev?: React.FormEvent<HTMLElement | HTMLInputElement>, option?: FluentUI.IChoiceGroupOption): void => {
            this._value = option.key;
            ev.stopPropagation();
            ev.preventDefault();
        }

    private handleComboBoxChange =
        (event: React.FormEvent<FluentUI.IComboBox>, option?: FluentUI.IComboBoxOption, index?: number, value?: string): void => {
            if (this.isMultiSelect) {
                this.updateMultiselectData(option.selected, option.key);
            } else {
                this._value = `${option.key}`;
            }
            event.stopPropagation();
            event.preventDefault();
        }

    private updateMultiselectData = (selected: boolean, key: any): void => {
        this.updateSelectedValues(selected, key);
        this._value = this._selectedValues.join(",");
    }

    private updateSelectedValues = (selected: boolean, key: any): void => {
        selected ? this._selectedValues.push(key) : this.removeItemFromArray(this._selectedValues, key);
    }

    private removeItemFromArray = (arr: any[], item: any): void => {
        const index = arr.indexOf(item);
        arr.splice(index, 1);
    }
}
