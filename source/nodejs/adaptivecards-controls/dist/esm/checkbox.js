import * as Constants from "./constants";
import { InputControl } from "./inputcontrol";
export class CheckBox extends InputControl {
    constructor() {
        super(...arguments);
        this._label = "";
        this._checkboxElement = null;
        this._spanElement = null;
    }
    static createId() {
        var result = CheckBox.creationIndex;
        CheckBox.creationIndex++;
        return result;
    }
    changed() {
        if (this.onChange) {
            this.onChange(this);
        }
    }
    keyDown(e) {
        switch (e.keyCode) {
            case Constants.KEY_ENTER:
                this.isChecked = !this.isChecked;
                break;
        }
    }
    attach(rootElement) {
        super.attach(rootElement);
        rootElement.className = "ms-ctrl ms-ctrl-checkbox";
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
        this._checkboxElement.id = "ms-ctrl-checkbox-" + CheckBox.createId();
        this._checkboxElement.type = "checkbox";
        this._checkboxElement.style.position = "absolute";
        this._checkboxElement.checked = this.isChecked;
        this._checkboxElement.onchange = (e) => { this.changed(); };
        var labelElement = document.createElement("label");
        labelElement.htmlFor = this._checkboxElement.id;
        this._spanElement = document.createElement("span");
        this._spanElement.innerText = this._label;
        labelElement.appendChild(this._spanElement);
        rootElement.innerHTML = "";
        rootElement.appendChild(this._checkboxElement);
        rootElement.appendChild(labelElement);
    }
    get label() {
        return this._label;
    }
    set label(value) {
        this._label = value;
        if (this._spanElement) {
            this._spanElement.innerText = this._label;
        }
    }
    get isChecked() {
        return this._isChecked;
    }
    set isChecked(value) {
        if (this._isChecked != value) {
            this._isChecked = value;
            if (this._checkboxElement) {
                this._checkboxElement.checked = this._isChecked;
            }
            this.changed();
        }
    }
}
// Used to generate unique Ids
CheckBox.creationIndex = 0;
//# sourceMappingURL=checkbox.js.map