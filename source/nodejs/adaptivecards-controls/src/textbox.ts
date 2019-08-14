// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Constants from "./constants";
import * as Utils from "./utils";
import { InputControl } from "./inputcontrol";

abstract class EditBox {
    protected changed() {
        if (this.onChange) {
            this.onChange();
        }
    }

    onChange: () => void;

    abstract get element(): HTMLElement;

    abstract set placeholder(value: string);
    abstract set lineCount(value: number);
    abstract set maxLength(value: number);

    abstract get value(): string;
    abstract set value(newValue: string);
}

class SingleLineEditBox extends EditBox {
    private _inputElement: HTMLInputElement;

    constructor() {
        super();

        this._inputElement = document.createElement("input");
        this._inputElement.className = "ms-ctrl ms-ctrl-textbox";
        this._inputElement.type = "text";
        this._inputElement.oninput = (e) => {
            this.changed();
        }
    }

    get element(): HTMLElement {
        return this._inputElement;
    }

    set placeholder(value: string) {
        this._inputElement.placeholder = value;
    }

    set lineCount(value: number) {
        // lineCount can't be set on a SingleLineEditBox
    }

    set maxLength(value: number) {
        if (this._inputElement.maxLength != value) {
            this._inputElement.maxLength = value;

            this.value = this.value.substr(0, value);
        }
    }

    get value(): string {
        return this._inputElement.value;
    }

    set value(newValue: string) {
        this._inputElement.value = newValue;
    }
}

class MultilineEditBox extends EditBox {
    private _textareaElement: HTMLTextAreaElement;

    constructor() {
        super();

        this._textareaElement = document.createElement("textarea");
        this._textareaElement.className = "ms-ctrl ms-ctrl-textbox ms-ctrl-textbox-multiline";
        this._textareaElement.oninput = (e) => {
            this.changed();
        }
    }

    get element(): HTMLElement {
        return this._textareaElement;
    }

    set placeholder(value: string) {
        this._textareaElement.placeholder = value;
    }

    set lineCount(value: number) {
        this._textareaElement.rows = value;
    }

    set maxLength(value: number) {
        if (this._textareaElement.maxLength != value) {
            this._textareaElement.maxLength = value;

            this.value = this.value.substr(0, value);
        }
    }

    get value(): string {
        return this._textareaElement.value;
    }

    set value(newValue: string) {
        this._textareaElement.value = newValue;
    }
}

export class TextBox extends InputControl {
    private _isMultiline: boolean = false;
    private _lineCount: number = 3;
    private _maxLength: number;
    private _placeholder: string;
    private _editBox: EditBox;

    private editBoxChanged() {
        if (this.onChange) {
            this.onChange(this);
        }
    }

    private recreateEditBox() {
        var currentValue: string = null;

        if (this._editBox) {
            currentValue = this._editBox.value;
        }
        else {
            currentValue = this.rootElement.innerText;
        }

        if (this._isMultiline) {
            this._editBox = new MultilineEditBox();
        }
        else {
            this._editBox = new SingleLineEditBox();
        }

        if (currentValue) {
            this._editBox.value = currentValue;
        }

        this._editBox.lineCount = this._lineCount;
        this._editBox.maxLength = this._maxLength;
        this._editBox.placeholder = this._placeholder;
        this._editBox.onChange = () => { this.editBoxChanged(); }

        this.rootElement.innerHTML = "";
        this.rootElement.appendChild(this._editBox.element);
    }

    private get editBox(): EditBox {
        if (!this._editBox) {
            this.recreateEditBox();
        }

        return this._editBox;
    }

    onChange: (sender: TextBox) => void;

    attach(rootElement: HTMLElement) {
        super.attach(rootElement);

        this._isMultiline = Utils.getAttributeValueAsBool(rootElement, "ismultiline", false);
        this._lineCount = Utils.getAttributeValueAsInt(rootElement, "lines", 3);
        this._maxLength = Utils.getAttributeValueAsInt(rootElement, "maxlength", 50000);
        this._placeholder = Utils.getAttributeValueAsString(rootElement, "placeholder", null);

        this.recreateEditBox();
    }

    get value(): string {
        return this.editBox.value;
    }

    set value(newValue: string) {
        this.editBox.value = newValue;
    }

    get placeholder(): string {
        return this._placeholder;
    }

    set placeholder(value: string) {
        this._placeholder = value;
        this.editBox.placeholder = value;
    }

    get isMultiline(): boolean {
        return this._isMultiline;
    }

    set isMultiline(value: boolean) {
        if (this._isMultiline != value) {
            this._isMultiline = value;

            this.recreateEditBox();
        }
    }

    get lineCount(): number {
        return this._lineCount;
    }

    set lineCount(value: number) {
        if (value > 0) {
            this._lineCount = value;
            this.editBox.lineCount = value;
        }
    }

    get maxLength(): number {
        return this._maxLength;
    }

    set maxLength(value: number) {
        if (value > 0) {
            this._maxLength = value;
            this.editBox.maxLength = value;
        }
    }
}
