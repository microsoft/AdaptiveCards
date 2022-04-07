// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { defaultHostConfig, HostConfig } from "../host-config";
import { Constants } from "./constants";

export class MenuItem {
    private _hostConfig?: HostConfig;
    private _element: HTMLElement;
    private _value: string;
    private _isEnabled: boolean = true;

    private click() {
        if (this.isEnabled && this.onClick) {
            this.onClick(this);
        }
    }

    private updateCssClasses() {
        if (this._element) {
            const effectiveHostConfig = this._hostConfig ? this._hostConfig : defaultHostConfig;

            this._element.className = effectiveHostConfig.makeCssClassName("ac-ctrl");
            this._element.classList.add(
                effectiveHostConfig.makeCssClassName(
                    this.isEnabled ? "ac-ctrl-dropdown-item" : "ac-ctrl-dropdown-item-disabled"
                )
            );

            if (!this.isEnabled) {
                this._element.classList.add(effectiveHostConfig.makeCssClassName("ac-disabled"));
            }
        }
    }

    readonly key: string;

    onClick?: (item: MenuItem) => void;

    constructor(key: string, value: string) {
        this.key = key;
        this._value = value;
    }

    toString(): string {
        return this.value;
    }

    render(hostConfig?: HostConfig): HTMLElement {
        this._hostConfig = hostConfig;

        if (!this._element) {
            this._element = document.createElement("span");
            this._element.innerText = this.value;
            this._element.setAttribute("role", "menuitem");

            if (!this.isEnabled) {
                this._element.setAttribute("aria-disabled", "true");
            }

            this._element.setAttribute("aria-current", "false");
            this._element.onmouseup = (_e) => {
                this.click();
            };
            this._element.onkeydown = (e) => {
                if (e.key === Constants.keys.enter) {
                    e.cancelBubble = true;

                    this.click();
                }
            };

            this.updateCssClasses();
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

    get isEnabled(): boolean {
        return this._isEnabled;
    }

    set isEnabled(value: boolean) {
        if (this._isEnabled !== value) {
            this._isEnabled = value;

            this.updateCssClasses();
        }
    }
}
