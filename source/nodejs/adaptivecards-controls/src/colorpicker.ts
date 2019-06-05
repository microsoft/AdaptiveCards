// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { InputWithPopup, PopupControl } from "./inputwithpopup";
import { ColorPickerPanel, Color } from "./colorpicker-panel";

export class ColorPickerPopupControl extends PopupControl {
    private _owner: ColorPicker;
    private _colorPicker: ColorPickerPanel;

    constructor(owner: ColorPicker) {
        super();

        this._owner = owner;
    }

    protected renderContent(): HTMLElement {
        let element = document.createElement("div");
        element.className = "ms-ctrl ms-colorPickerPopup";

        this._colorPicker = new ColorPickerPanel();
        this._colorPicker.color = this._owner.value;
        this._colorPicker.onColorChanged = (c) => {
            this._owner.value = c.color;
        };

        element.appendChild(this._colorPicker.renderedElement);

        return element;
    }

    focus() {
        if (this._colorPicker) {
            this._colorPicker.focus();
        }
    }
}

export class ColorPicker extends InputWithPopup<ColorPickerPopupControl, Color> {
    protected validateRootElement(rootElement: HTMLElement) {
        if (!(rootElement instanceof HTMLDivElement)) {
            throw new Error("DatePicker requires a DIV element as its root.");
        }
    }

    protected createPopupControl(): ColorPickerPopupControl {
        return new ColorPickerPopupControl(this);
    }

    protected getValueAsString(): string {
        return this.value.toColorCode();
    }

    protected getCssClassName(): string {
        return "ms-ctrl ms-ctrl-colorPicker";
    }

    protected getButtonIconCssClassName(): string {
        return "ms-icon-color";
    }

    protected renderValue(): string | HTMLElement {
        if (this.value) {
            let element = document.createElement("div");
            element.style.height = "65%";
            element.style.display = "flex";
            element.style.alignItems = "center";

            let colorSample = document.createElement("div");
            colorSample.style.border = "1px solid #CCCCCC";
            colorSample.style.width = "30px";
            colorSample.style.height = "100%";
            colorSample.style.backgroundColor = this.value.toCssColor();

            let colorName = document.createElement("div");
            colorName.style.marginLeft = "4px";
            colorName.innerText = this.value.toColorCode();

            element.append(colorSample, colorName);

            return element;
        }
        else {
            return super.renderValue();
        }
    }

    popup() {
        super.popup();

        if (this.isOpen) {
            this.popupControl.focus();
        }
    }
}