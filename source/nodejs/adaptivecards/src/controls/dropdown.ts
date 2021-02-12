// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Constants } from "./constants";

export class DropDownItem {
    private _element: HTMLElement;
    private _value: string;

    private click() {
        if (this.onClick) {
            this.onClick(this);
        }
    }

    readonly key: string;

    onClick?: (item: DropDownItem) => void;

    constructor(key: string, value: string) {
        this.key = key;
        this._value = value;
    }

    toString(): string {
        return this.value;
    }

    render(): HTMLElement {
        if (!this._element) {
            this._element = document.createElement("span");
            this._element.className = "ms-ctrl ms-ctrl-dropdown-item";
            this._element.innerText = this.value;
            this._element.setAttribute("role", "menuitem");
            this._element.setAttribute("aria-selected", "false");
            this._element.onmouseup = (e) => { this.click(); };
            this._element.onkeydown = (e) => {
                if (e.key === Constants.keys.enter) {
                    this.click();
                    e.cancelBubble = true;
                }
            };
        }

        return this._element;
    }

    get value(): string {
        return this._value;
    }

    set value(newValue: string) {
        this._value = newValue;

        if (this._element) {
            this._element.innerText = newValue;
        }
    }
}
