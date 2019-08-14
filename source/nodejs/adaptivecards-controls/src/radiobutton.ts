// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Constants from "./constants";
import { InputControl } from "./inputcontrol";

export class RadioButton extends InputControl {
    // Used to generate unique Ids
    private static creationIndex = 0;

    private static createId(): number {
        var result = RadioButton.creationIndex;

        RadioButton.creationIndex++;

        return result;
    }

    private _label: string = "";
    private _isChecked: boolean;
    private _checkboxElement: HTMLInputElement = null;
    private _spanElement: HTMLSpanElement = null;

    private changed() {
        if (this.onChange) {
            this.onChange(this);
        }
    }

    protected keyDown(e: KeyboardEvent) {
        switch (e.keyCode) {
            case Constants.KEY_ENTER:
                this.isChecked = !this.isChecked;
                break;
        }
    }

    onChange: (sender: RadioButton) => void;

    attach(rootElement: HTMLElement) {
        super.attach(rootElement);

        rootElement.className = "ms-ctrl ms-ctrl-radiobutton";
        rootElement.tabIndex = 0;

        var labelAttribute = rootElement.attributes["label"];

        if (labelAttribute) {
            this._label = labelAttribute.value;
        }

        var isCheckedAttribute = rootElement.attributes["ischecked"];

        if (isCheckedAttribute) {
            this._isChecked = isCheckedAttribute.value === "true";
        }

        this._checkboxElement = document.createElement("input");
        this._checkboxElement.id = "ms-ctrl-radio-" + RadioButton.createId();
        this._checkboxElement.type = "radio";
        this._checkboxElement.style.position = "absolute";
        this._checkboxElement.checked = this.isChecked;
        this._checkboxElement.onchange = (e) => { this.changed() };

        var groupNameAttribute = rootElement.attributes["groupname"];

        if (groupNameAttribute) {
            this._checkboxElement.name = groupNameAttribute.value;
        }

        var labelElement = document.createElement("label")
        labelElement.htmlFor = this._checkboxElement.id;

        this._spanElement = document.createElement("span");
        this._spanElement.innerText = this._label;

        labelElement.appendChild(this._spanElement);

        rootElement.innerHTML = "";
        rootElement.appendChild(this._checkboxElement);
        rootElement.appendChild(labelElement);
    }

    get label(): string {
        return this._label;
    }

    set label(value: string) {
        this._label = value;

        if (this._spanElement) {
            this._spanElement.innerText = this._label;
        }
    }

    get isChecked(): boolean {
        return this._isChecked;
    }

    set isChecked(value: boolean) {
        if (this._isChecked != value) {
            this._isChecked = value;

            if (this._checkboxElement) {
                this._checkboxElement.checked = this._isChecked;
            }

            this.changed();
        }
    }
}
