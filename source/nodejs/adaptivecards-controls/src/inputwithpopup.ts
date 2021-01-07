// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Constants from "./constants";
import * as Utils from "./utils";
import { InputControl } from "./inputcontrol";

export abstract class PopupControl {
    private _isOpen: boolean = false;
    private _overlayElement: HTMLElement;
    private _popupElement: HTMLElement;

    protected abstract renderContent(): HTMLElement;

    onClose: (popupControl: PopupControl, wasCancelled: boolean) => void;

    keyDown(e: KeyboardEvent) {
        switch (e.keyCode) {
            case Constants.KEY_ESCAPE:
                this.closePopup(true);

                break;
        }
    }

    render(rootElementBounds: ClientRect): HTMLElement {
        let element = document.createElement("div");
        element.tabIndex = 0;
        element.className = "ms-ctrl ms-ctrl-popup-container";
        element.onkeydown = (e) => {
            this.keyDown(e);

            return !e.cancelBubble;
        };

        element.appendChild(this.renderContent());

        return element;
    }

    focus() {
        if (this._popupElement) {
            (<HTMLElement>this._popupElement.firstElementChild).focus();
        }
    }

    popup(rootElement: HTMLElement) {
        if (!this._isOpen) {
            this._overlayElement = document.createElement("div");
            this._overlayElement.className = "ms-ctrl-overlay";
            this._overlayElement.tabIndex = 0;
            this._overlayElement.style.width = document.documentElement.scrollWidth + "px";
            this._overlayElement.style.height = document.documentElement.scrollHeight + "px";
            this._overlayElement.onfocus = (e) => { this.closePopup(true); };

            document.body.appendChild(this._overlayElement);

            var rootElementBounds = rootElement.getBoundingClientRect();

            this._popupElement = this.render(rootElementBounds);
            this._popupElement.classList.remove(
                "ms-ctrl-slide",
                "ms-ctrl-slideLeftToRight",
                "ms-ctrl-slideRightToLeft",
                "ms-ctrl-slideTopToBottom",
                "ms-ctrl-slideRightToLeft");

            this._overlayElement.appendChild(this._popupElement);

            var popupElementBounds = this._popupElement.getBoundingClientRect();

            var availableSpaceBelow = window.innerHeight - rootElementBounds.bottom;
            var availableSpaceAbove = rootElementBounds.top;
            var availableSpaceRight = window.innerWidth - rootElementBounds.left;
            var availableSpaceRight = window.innerWidth - rootElementBounds.right;
            var availableSpaceLeft = rootElementBounds.left;

            var left = rootElementBounds.left + Utils.getScrollX();
            var top;

            if (availableSpaceAbove < popupElementBounds.height && availableSpaceBelow < popupElementBounds.height) {
                // Not enough space above or below root element
                var actualPopupHeight = Math.min(popupElementBounds.height, window.innerHeight);

                this._popupElement.style.maxHeight = actualPopupHeight + "px";

                if (actualPopupHeight < popupElementBounds.height) {
                    top = Utils.getScrollY();
                }
                else {
                    top = Utils.getScrollY() + rootElementBounds.top + (rootElementBounds.height - actualPopupHeight) /2;
                }

                if (availableSpaceLeft < popupElementBounds.width && availableSpaceRight < popupElementBounds.width) {
                    // Not enough space left or right of root element
                    var actualPopupWidth = Math.min(popupElementBounds.width, window.innerWidth);

                    this._popupElement.style.maxWidth = actualPopupWidth + "px";

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

                        this._popupElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideLeftToRight");
                    }
                    else {
                        left = Utils.getScrollX() + rootElementBounds.left - popupElementBounds.width;

                        this._popupElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideRightToLeft");
                    }
                }
            }
            else {
                // Enough space above or below root element
                if (availableSpaceBelow >= popupElementBounds.height) {
                    top = Utils.getScrollY() + rootElementBounds.bottom;

                    this._popupElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideTopToBottom");
                }
                else {
                    top = Utils.getScrollY() + rootElementBounds.top - popupElementBounds.height

                    this._popupElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideBottomToTop");
                }

                if (availableSpaceRight < popupElementBounds.width) {
                    left = Utils.getScrollX() + rootElementBounds.right - popupElementBounds.width;
                }
            }

            this._popupElement.style.left = left + "px";
            this._popupElement.style.top = top + "px";

            this._popupElement.focus();

            this._isOpen = true;
        }
    }

    closePopup(wasCancelled: boolean) {
        if (this._isOpen) {
            document.body.removeChild(this._overlayElement);

            this._isOpen = false;

            if (this.onClose) {
                this.onClose(this, wasCancelled);
            }
        }
    }

    get isOpen(): boolean {
        return this._isOpen;
    }
}

export abstract class InputWithPopup<TPopupControl extends PopupControl, TValue> extends InputControl {
    private _labelElement: HTMLElement;
    private _dropDownButtonElement: HTMLElement;
    private _popupControl: TPopupControl;
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

        window.addEventListener("resize", (e) => { this.closePopup(true); });

        this.rootElement.onclick = (e) => {
            if (this.isOpen) {
                this.closePopup(true);
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
        this._popupControl = this.createPopupControl();
        this._popupControl = this.createPopupControl();
        this._popupControl.onClose = (sender, wasCancelled) => {
            this.closePopup(wasCancelled);

            this.rootElement.focus();
        };

        this._popupControl.popup(this.rootElement);
    }

    closePopup(wasCancelled: boolean) {
        if (this.popupControl) {
            this.popupControl.closePopup(wasCancelled);
        }
    }

    get isOpen(): boolean {
        return this._popupControl ? this._popupControl.isOpen : false;
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
