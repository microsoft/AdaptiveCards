// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Constants from "./constants";
import * as Utils from "./utils";
import { InputControl } from "./inputcontrol";

export abstract class PopupControl {
    private _popupElement: HTMLElement;

    protected abstract renderContent(): HTMLElement;

    protected close() {
        if (this.onClose) {
            this.onClose(this);
        }
    }

    onClose: (popupControl: PopupControl) => void;

    keyDown(e: KeyboardEvent) {
        switch (e.keyCode) {
            case Constants.KEY_ESCAPE:
                this.close();

                break;
        }
    }

    render(rootElementBounds: ClientRect): HTMLElement {
        this._popupElement = document.createElement("div");
        this._popupElement.tabIndex = 0;
        this._popupElement.className = "ms-ctrl ms-ctrl-popup-container";
        this._popupElement.onkeydown = (e) => {
            this.keyDown(e);

            return !e.cancelBubble;
        };

        this._popupElement.appendChild(this.renderContent());

        return this._popupElement;
    }

    focus() {
        if (this._popupElement) {
            (<HTMLElement>this._popupElement.firstElementChild).focus();
        }
    }
}

export abstract class InputWithPopup<TPopupControl extends PopupControl, TValue> extends InputControl {
    private _isOpen: boolean;
    private _labelElement: HTMLElement;
    private _dropDownButtonElement: HTMLElement;
    private _overlayElement: HTMLElement;
    private _popupControl: TPopupControl;
    private _popupControlElement: HTMLElement;
    private _placeholderText: string;
    private _value: TValue;

    protected keyDown(e: KeyboardEvent) {
        switch (e.keyCode) {
            case Constants.KEY_ENTER:
                this.popup();
                break;
        }
    }

    private updateLabel() {
        if (this._labelElement) {
            if (this._value) {
                this._labelElement.innerHTML = this.getValueAsString();
                this._labelElement.classList.remove("placeholder");
            }
            else {
                this._labelElement.innerText = this._placeholderText ? this._placeholderText : "";
                this._labelElement.classList.add("placeholder");
            }
        }
    }

    protected get popupControl(): TPopupControl {
        return this._popupControl;
    }

    protected abstract createPopupControl(): TPopupControl;
    protected abstract getCssClassName(): string;

    protected getButtonIconCssClassName(): string {
        return "ms-icon-chevronDown";
    }

    protected getValueAsString(): string {
        return this._value.toString();
    }

    protected valueChanged() {
        if (this.onValueChanged) {
            this.onValueChanged(this);
        }
    }

    onValueChanged: (sender: InputControl) => void;

    attach(rootElement: HTMLElement) {
        super.attach(rootElement);

        rootElement.tabIndex = 0;
        rootElement.className = this.getCssClassName();

        window.addEventListener("resize", (e) => { this.closePopup(); });

        this.rootElement.onclick = (e) => {
            if (this._isOpen) {
                this.closePopup();
            }
            else {
                this.popup();
            }
        };

        let placeHolderDomItem = this.rootElement.attributes.getNamedItem("placeholder");

        if (placeHolderDomItem) {
            this._placeholderText = placeHolderDomItem.value;
        }

        this._labelElement = document.createElement("span");
        this._labelElement.className = "ms-ctrl ms-dropdown-label";

        this._dropDownButtonElement = document.createElement("i");
        this._dropDownButtonElement.className = "ms-icon ms-ctrl-dropdown-button " + this.getButtonIconCssClassName();

        this.rootElement.appendChild(this._labelElement);
        this.rootElement.appendChild(this._dropDownButtonElement);

        this.updateLabel();
    }

    popup() {
        if (!this._isOpen) {
            this._overlayElement = document.createElement("div");
            this._overlayElement.className = "ms-ctrl-overlay";
            this._overlayElement.tabIndex = 0;
            this._overlayElement.style.width = document.documentElement.scrollWidth + "px";
            this._overlayElement.style.height = document.documentElement.scrollHeight + "px";
            this._overlayElement.onfocus = (e) => { this.closePopup(); };

            document.body.appendChild(this._overlayElement);

            this._popupControl = this.createPopupControl();
            this._popupControl.onClose = (sender) => {
                this.closePopup();

                this.rootElement.focus();
            };

            var rootElementBounds = this.rootElement.getBoundingClientRect();

            this._popupControlElement = this._popupControl.render(rootElementBounds);
            this._popupControlElement.classList.remove(
                "ms-ctrl-slide",
                "ms-ctrl-slideLeftToRight",
                "ms-ctrl-slideRightToLeft",
                "ms-ctrl-slideTopToBottom",
                "ms-ctrl-slideRightToLeft");

            this._overlayElement.appendChild(this._popupControlElement);

            var popupElementBounds = this._popupControlElement.getBoundingClientRect();

            var availableSpaceBelow = window.innerHeight - rootElementBounds.bottom;
            var availableSpaceAbove = rootElementBounds.top;

            var left = rootElementBounds.left + Utils.getScrollX();
            var top;

            if (availableSpaceAbove < popupElementBounds.height && availableSpaceBelow < popupElementBounds.height) {
                // Not enough space above or below root element
                var actualPopupHeight = Math.min(popupElementBounds.height, window.innerHeight);

                this._popupControlElement.style.maxHeight = actualPopupHeight + "px";

                if (actualPopupHeight < popupElementBounds.height) {
                    top = Utils.getScrollY();
                }
                else {
                    top = Utils.getScrollY() + rootElementBounds.top + (rootElementBounds.height - actualPopupHeight) /2;
                }

                var availableSpaceRight = window.innerWidth - rootElementBounds.right;
                var availableSpaceLeft = rootElementBounds.left;

                if (availableSpaceLeft < popupElementBounds.width && availableSpaceRight < popupElementBounds.width) {
                    // Not enough space left or right of root element
                    var actualPopupWidth = Math.min(popupElementBounds.width, window.innerWidth);

                    this._popupControlElement.style.maxWidth = actualPopupWidth + "px";

                    if (actualPopupWidth < popupElementBounds.width) {
                        left = Utils.getScrollX();
                    }
                    else {
                        left = Utils.getScrollX() + rootElementBounds.left + (rootElementBounds.width - actualPopupWidth) /2;
                    }
                }
                else {
                    // Enough space on the left or right of the root element
                    if (availableSpaceRight >= popupElementBounds.width) {
                        left = Utils.getScrollX() + rootElementBounds.right;

                        this._popupControlElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideLeftToRight");
                    }
                    else {
                        left = Utils.getScrollX() + rootElementBounds.left - popupElementBounds.width;

                        this._popupControlElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideRightToLeft");
                    }
                }
            }
            else {
                // Enough space above or below root element
                if (availableSpaceBelow >= popupElementBounds.height) {
                    top = Utils.getScrollY() + rootElementBounds.bottom;

                    this._popupControlElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideTopToBottom");
                }
                else {
                    top = Utils.getScrollY() + rootElementBounds.top - popupElementBounds.height

                    this._popupControlElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideBottomToTop");
                }
            }

            this._popupControlElement.style.left = left + "px";
            this._popupControlElement.style.top = top + "px";

            this._popupControlElement.focus();

            this._isOpen = true;
        }
    }

    closePopup() {
        if (this._isOpen) {
            document.body.removeChild(this._overlayElement);

            this._isOpen = false;
        }
    }

    get isOpen(): boolean {
        return this._isOpen;
    }

    get placeholderText(): string {
        return this._placeholderText;
    }

    set placeholderText(value: string) {
        this._placeholderText = value;
    }

    get value(): TValue {
        return this._value;
    }

    set value(newValue: TValue) {
        if (this._value != newValue) {
            this._value = newValue;

            this.updateLabel();
            this.valueChanged();
        }
    }
}
