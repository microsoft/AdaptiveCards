// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Constants } from "./constants";
import * as Utils from "../utils";
import { defaultHostConfig, HostConfig } from "../host-config";

export abstract class PopupControl {
    private _isOpen: boolean = false;
    private _overlayElement: HTMLElement;
    private _popupElement: HTMLElement;
    private _hostConfig?: HostConfig;

    protected abstract renderContent(): HTMLElement;

    onClose: (popupControl: PopupControl, wasCancelled: boolean) => void;

    keyDown(e: KeyboardEvent) {
        switch (e.key) {
            case Constants.keys.escape:
                this.closePopup(true);

                break;
        }
    }

    render(_rootElementBounds: ClientRect): HTMLElement {
        const element = document.createElement("div");
        element.tabIndex = 0;
        element.className = this.hostConfig.makeCssClassName("ac-ctrl", "ac-ctrl-popup-container");
        element.setAttribute("role", "dialog");
        element.setAttribute("aria-modal", "true");
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
            this._overlayElement.className = this.hostConfig.makeCssClassName("ac-ctrl-overlay");
            this._overlayElement.tabIndex = 0;
            this._overlayElement.style.width = document.documentElement.scrollWidth + "px";
            this._overlayElement.style.height = document.documentElement.scrollHeight + "px";
            this._overlayElement.onfocus = (_e) => {
                this.closePopup(true);
            };

            document.body.appendChild(this._overlayElement);

            const rootElementBounds = rootElement.getBoundingClientRect();

            this._popupElement = this.render(rootElementBounds);
            this._popupElement.classList.remove(
                ...this.hostConfig.makeCssClassNames(
                    "ac-ctrl-slide",
                    "ac-ctrl-slideLeftToRight",
                    "ac-ctrl-slideRightToLeft",
                    "ac-ctrl-slideTopToBottom",
                    "ac-ctrl-slideRightToLeft"
                )
            );

            window.addEventListener("resize", (_e) => {
                this.closePopup(true);
            });

            const rootElementLabel = rootElement.getAttribute("aria-label");
            if (rootElementLabel) {
                this._popupElement.setAttribute("aria-label", rootElementLabel);
            }

            this._overlayElement.appendChild(this._popupElement);

            const popupElementBounds = this._popupElement.getBoundingClientRect();

            const availableSpaceBelow = window.innerHeight - rootElementBounds.bottom;
            const availableSpaceAbove = rootElementBounds.top;
            const availableSpaceRight = window.innerWidth - rootElementBounds.right;
            const availableSpaceLeft = rootElementBounds.left;

            let left = rootElementBounds.left + Utils.getScrollX();
            let top;

            if (
                availableSpaceAbove < popupElementBounds.height &&
                availableSpaceBelow < popupElementBounds.height
            ) {
                // Not enough space above or below root element
                const actualPopupHeight = Math.min(popupElementBounds.height, window.innerHeight);

                this._popupElement.style.maxHeight = actualPopupHeight + "px";

                if (actualPopupHeight < popupElementBounds.height) {
                    top = Utils.getScrollY();
                } else {
                    top =
                        Utils.getScrollY() +
                        rootElementBounds.top +
                        (rootElementBounds.height - actualPopupHeight) / 2;
                }

                if (
                    availableSpaceLeft < popupElementBounds.width &&
                    availableSpaceRight < popupElementBounds.width
                ) {
                    // Not enough space left or right of root element
                    const actualPopupWidth = Math.min(popupElementBounds.width, window.innerWidth);

                    this._popupElement.style.maxWidth = actualPopupWidth + "px";

                    if (actualPopupWidth < popupElementBounds.width) {
                        left = Utils.getScrollX();
                    } else {
                        left =
                            Utils.getScrollX() +
                            rootElementBounds.left +
                            (rootElementBounds.width - actualPopupWidth) / 2;
                    }
                } else {
                    // Enough space on the left or right of the root element
                    if (availableSpaceRight >= popupElementBounds.width) {
                        left = Utils.getScrollX() + rootElementBounds.right;

                        this._popupElement.classList.add(
                            ...this.hostConfig.makeCssClassNames(
                                "ac-ctrl-slide",
                                "ac-ctrl-slideLeftToRight"
                            )
                        );
                    } else {
                        left =
                            Utils.getScrollX() + rootElementBounds.left - popupElementBounds.width;

                        this._popupElement.classList.add(
                            ...this.hostConfig.makeCssClassNames(
                                "ac-ctrl-slide",
                                "ac-ctrl-slideRightToLeft"
                            )
                        );
                    }
                }
            } else {
                // Enough space above or below root element
                if (availableSpaceBelow >= popupElementBounds.height) {
                    top = Utils.getScrollY() + rootElementBounds.bottom;

                    this._popupElement.classList.add(
                        ...this.hostConfig.makeCssClassNames(
                            "ac-ctrl-slide",
                            "ac-ctrl-slideTopToBottom"
                        )
                    );
                } else {
                    top = Utils.getScrollY() + rootElementBounds.top - popupElementBounds.height;

                    this._popupElement.classList.add(
                        ...this.hostConfig.makeCssClassNames(
                            "ac-ctrl-slide",
                            "ac-ctrl-slideBottomToTop"
                        )
                    );
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

    get hostConfig(): HostConfig {
        return this._hostConfig ? this._hostConfig : defaultHostConfig;
    }

    set hostConfig(value: HostConfig) {
        this._hostConfig = value;
    }

    get isOpen(): boolean {
        return this._isOpen;
    }
}
