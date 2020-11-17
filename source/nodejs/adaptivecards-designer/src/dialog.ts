// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Constants } from "adaptivecards-controls";

export class DialogButton {
    onClick: (sender: DialogButton) => void;

    constructor(public caption: string) {}

    render(): HTMLElement {
        let element = document.createElement("button");
        element.className = "acd-dialog-button";
        element.innerText = this.caption;
        element.onclick = (e) => {
            this.clicked();
        }

        return element;
    }

    clicked() {
        if (this.onClick) {
            this.onClick(this);
        }
    }
}

export abstract class Dialog {
    private _overlayElement: HTMLElement;
    private _isOpen: boolean = false;
    private _originalFocusedElement: HTMLElement;
    private _firstFocusableElement: HTMLElement;
    private _lastFocusableElement: HTMLElement;

    protected abstract renderContent(): HTMLElement;

    onClose: (sender: Dialog) => void = null;

    readonly closeButton: DialogButton;

    title: string;
    width: string;
    height: string;
    // flag to prevent dialog close on overlay element click, default it's set to false, for Pi2Card it will be set to true
    preventLightDismissal: boolean = false;

    constructor() {
        this.closeButton = new DialogButton("Close");
        this.closeButton.onClick = (sender) => {
            this.close();
        }
    }

    open() {
        if (!this._isOpen) {
            this._originalFocusedElement = document.activeElement as HTMLElement;

            this._overlayElement = document.createElement("div");
            this._overlayElement.className = "acd-dialog-overlay";
            this._overlayElement.onclick = (e) => {
                // clicks on the overlay window should dismiss the dialog
                if (!this.preventLightDismissal) { this.close(); }
            };

            let dialogFrameElement = document.createElement("div");
            dialogFrameElement.className = "acd-dialog-frame";
            dialogFrameElement.style.width = this.width;
            dialogFrameElement.style.height = this.height;
            dialogFrameElement.style.justifyContent = "space-between";
            dialogFrameElement.setAttribute("aria-modal", "true");
            dialogFrameElement.setAttribute("role", "dialog");
            dialogFrameElement.setAttribute("aria-labelledby", "acd-dialog-title-element");
            dialogFrameElement.tabIndex = -1;

            dialogFrameElement.onclick = (e) => {
                // disable click bubbling from the frame element -- otherwise it'll get to the overlay, closing the
                // dialog unexpectedly
                if (!this.preventLightDismissal) {
                    e.cancelBubble = true;
                    return false;
                }
            }

            // keyboard navigation support
            dialogFrameElement.onkeydown = (e) => {
                switch (e.key) {
                    case Constants.keys.tab:
                        if (e.shiftKey && document.activeElement === this._firstFocusableElement) {
                            // backwards tab on first element. set focus on last
                            e.preventDefault();
                            this._lastFocusableElement.focus();
                        }
                        else if (!e.shiftKey && document.activeElement === this._lastFocusableElement) {
                            // forward tab on last element
                            e.preventDefault();
                            this._firstFocusableElement.focus();
                        }
                        break;

                    case Constants.keys.escape:
                        this.close();
                        e.preventDefault();
                        e.cancelBubble = true;
                        break;
                }

                return !e.cancelBubble;
            };

            let titleBarElement = document.createElement("div");
            titleBarElement.style.display = "flex";
            titleBarElement.style.alignItems = "center";
            titleBarElement.style.flex = "0 0 auto";
            titleBarElement.style.marginBottom = "10px";

            let titleElement = document.createElement("div");
            titleElement.className = "acd-dialog-title";
            titleElement.id = "acd-dialog-title-element";
            titleElement.innerText = this.title;
            titleElement.style.flex = "1 1 auto";

            let xButton = document.createElement("button");
            xButton.className = "acd-icon acd-dialog-titleBar-button acd-icon-remove";
            xButton.style.flex = "0 0 auto";
            xButton.title = "Close";
            xButton.onclick = (e) => { this.close(); }

            titleBarElement.appendChild(titleElement);
            titleBarElement.appendChild(xButton);

            let contentElement = this.renderContent();
            contentElement.style.flex = "1 1 auto";

            let buttonBarElement = document.createElement("div");
            buttonBarElement.className = "acd-dialog-buttonBar";
            buttonBarElement.style.flex = "0 0 auto";
            buttonBarElement.appendChild(this.closeButton.render());

            dialogFrameElement.appendChild(titleBarElement);
            dialogFrameElement.appendChild(contentElement);
            dialogFrameElement.appendChild(buttonBarElement);

            this._overlayElement.appendChild(dialogFrameElement);

            document.body.appendChild(this._overlayElement);

            let focusableElements = dialogFrameElement.querySelectorAll('a[href], area[href], input:not([disabled]), select:not([disabled]), textarea:not([disabled]), button:not([disabled]), [tabindex="0"]');
            this._firstFocusableElement = focusableElements[0] as HTMLElement;
            this._lastFocusableElement = focusableElements[focusableElements.length-1] as HTMLElement;

            this._firstFocusableElement.focus();

            this._isOpen = true;
        }
    }

    close() {
        if (this._isOpen) {
            document.body.removeChild(this._overlayElement);

            this._isOpen = false;

            if (this.onClose) {
                this.onClose(this);
            }
            // Removing the focus action on close, it has been handled via onClose method of Dialog consume place.
            // this._originalFocusedElement.focus();
            this._originalFocusedElement = null;
        }
    }
}
