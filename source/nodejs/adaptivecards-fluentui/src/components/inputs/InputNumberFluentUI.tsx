// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as AC from "adaptivecards";
import * as FluentUI from "@fluentui/react";
import * as Shared from "../../utils/shared";

export class InputNumberFluentUI extends AC.NumberInput {

	protected handleChange = (event: React.FormEvent<HTMLInputElement | HTMLTextAreaElement>, newValue?: string) => {
		this._value = newValue;
    }

	private _value;
	public get value(): any {
		return this._value;
	}

	public isSet(): any {
		return this._value ? true : false
	}

	protected internalRender(): HTMLElement {
		if(this.defaultValue) {
			this._value = this.defaultValue;
		}

        const element = Shared.sharedInternalRender(this.renderReact);
        element.style.width = "100%";
        return element;
    }

    protected renderReact = (): JSX.Element => (
        <FluentUI.TextField
            id={this.id}
            placeholder={`${this.placeholder}`}
            defaultValue={`${this.defaultValue}`}
            type="number"
            max={this.max}
            min={this.min}
            onChange={this.handleChange}
        />
    )

}
