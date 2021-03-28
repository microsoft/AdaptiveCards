// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as AC from "adaptivecards";
import * as FluentUI from "@fluentui/react";
import * as Shared from "../../utils/shared";

export class InputToggleFluentUI extends AC.ToggleInput {

	private handleToggleChange = (event: React.MouseEvent<HTMLElement> | React.ChangeEvent, checked?: boolean) => {
        this._value = checked ? this.valueOn : this.valueOff;
    }
	
	private _value;
	public get value(): any {
		return this._value;
	}

	public isSet(): any {
		return this._value ? true : false;
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
        <FluentUI.Toggle
            id={this.id}
            inlineLabel={true}
            onChange={this.handleToggleChange}
            defaultChecked={this.defaultValue === this.valueOn}
            label={this.title}
            styles={{
                root: {
                    marginBottom: 0,
                    marginTop: 0,
                },
            }}
        />
    )

 
}
