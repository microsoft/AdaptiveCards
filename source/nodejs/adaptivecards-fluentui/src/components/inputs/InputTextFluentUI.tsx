// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as FluentUI from "@fluentui/react";
import * as AC from "adaptivecards";
import * as Shared from "../../utils/shared";

export class InputTextFluentUI extends AC.TextInput {
	protected handleChange = (event: React.FormEvent<HTMLInputElement | HTMLTextAreaElement>, newValue?: string) => {
		this._value = newValue;
    }

	private _value;
	public get value(): any
	{
		return this._value || this.defaultValue;
	}

	public isSet(): any {
		return this._value !== undefined || this.defaultValue !== undefined;
	}
	
	protected internalRender(): HTMLElement {
        const element = Shared.sharedInternalRender(this.renderReact);
        element.style.width = "100%";
        return element;
    }

    private renderReact = (): JSX.Element => {
        return (
            <FluentUI.TextField
                id={this.id}
                type={AC.InputTextStyle[this.style].toLowerCase()}
				defaultValue={this.defaultValue}
				multiline={this.isMultiline}
                maxLength={this.maxLength ? this.maxLength : undefined}
                placeholder={this.placeholder}
				required={this.isRequired}
                //label={this.label}
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
