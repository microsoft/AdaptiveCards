import * as Utils from "./utils";
import { InputControl } from "./inputcontrol";
class EditBox {
    changed() {
        if (this.onChange) {
            this.onChange();
        }
    }
}
class SingleLineEditBox extends EditBox {
    constructor() {
        super();
        this._inputElement = document.createElement("input");
        this._inputElement.className = "ms-ctrl ms-ctrl-textbox";
        this._inputElement.type = "text";
        this._inputElement.oninput = (e) => {
            this.changed();
        };
    }
    get element() {
        return this._inputElement;
    }
    set placeholder(value) {
        this._inputElement.placeholder = value;
    }
    set lineCount(value) {
        // lineCount can't be set on a SingleLineEditBox
    }
    set maxLength(value) {
        if (this._inputElement.maxLength != value) {
            this._inputElement.maxLength = value;
            this.value = this.value.substr(0, value);
        }
    }
    get value() {
        return this._inputElement.value;
    }
    set value(newValue) {
        this._inputElement.value = newValue;
    }
}
class MultilineEditBox extends EditBox {
    constructor() {
        super();
        this._textareaElement = document.createElement("textarea");
        this._textareaElement.className = "ms-ctrl ms-ctrl-textbox ms-ctrl-textbox-multiline";
        this._textareaElement.oninput = (e) => {
            this.changed();
        };
    }
    get element() {
        return this._textareaElement;
    }
    set placeholder(value) {
        this._textareaElement.placeholder = value;
    }
    set lineCount(value) {
        this._textareaElement.rows = value;
    }
    set maxLength(value) {
        if (this._textareaElement.maxLength != value) {
            this._textareaElement.maxLength = value;
            this.value = this.value.substr(0, value);
        }
    }
    get value() {
        return this._textareaElement.value;
    }
    set value(newValue) {
        this._textareaElement.value = newValue;
    }
}
export class TextBox extends InputControl {
    constructor() {
        super(...arguments);
        this._isMultiline = false;
        this._lineCount = 3;
    }
    editBoxChanged() {
        if (this.onChange) {
            this.onChange(this);
        }
    }
    recreateEditBox() {
        var currentValue = null;
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
        this._editBox.onChange = () => { this.editBoxChanged(); };
        this.rootElement.innerHTML = "";
        this.rootElement.appendChild(this._editBox.element);
    }
    get editBox() {
        if (!this._editBox) {
            this.recreateEditBox();
        }
        return this._editBox;
    }
    attach(rootElement) {
        super.attach(rootElement);
        this._isMultiline = Utils.getAttributeValueAsBool(rootElement, "ismultiline", false);
        this._lineCount = Utils.getAttributeValueAsInt(rootElement, "lines", 3);
        this._maxLength = Utils.getAttributeValueAsInt(rootElement, "maxlength", 50000);
        this._placeholder = Utils.getAttributeValueAsString(rootElement, "placeholder", null);
        this.recreateEditBox();
    }
    get value() {
        return this.editBox.value;
    }
    set value(newValue) {
        this.editBox.value = newValue;
    }
    get placeholder() {
        return this._placeholder;
    }
    set placeholder(value) {
        this._placeholder = value;
        this.editBox.placeholder = value;
    }
    get isMultiline() {
        return this._isMultiline;
    }
    set isMultiline(value) {
        if (this._isMultiline != value) {
            this._isMultiline = value;
            this.recreateEditBox();
        }
    }
    get lineCount() {
        return this._lineCount;
    }
    set lineCount(value) {
        if (value > 0) {
            this._lineCount = value;
            this.editBox.lineCount = value;
        }
    }
    get maxLength() {
        return this._maxLength;
    }
    set maxLength(value) {
        if (value > 0) {
            this._maxLength = value;
            this.editBox.maxLength = value;
        }
    }
}
//# sourceMappingURL=textbox.js.map