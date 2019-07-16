// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Utils from "./utils";
import * as Constants from "./constants";
import { Collection } from "./collection";
import { PopupControl } from "./inputwithpopup";
import { DropDownItem } from "./dropdown";

export class PopupMenu extends PopupControl {
    private _overlayElement: HTMLElement;
    private _popupControlElement: HTMLElement;
    private _isOpen: boolean;
    private _items: Collection<DropDownItem> = new Collection<DropDownItem>();
    private _renderedItems: Array<HTMLElement> = [];
    private _selectedIndex: number = -1;

    constructor() {
        super();
    }

    protected renderContent(): HTMLElement {
        var element = document.createElement("div");
        element.className = "ms-ctrl ms-popup";

        for (var i = 0; i < this._items.length; i++) {
            var renderedItem = this._items.get(i).render();
            renderedItem.tabIndex = 0;

            element.appendChild(renderedItem);

            if (i == this.selectedIndex) {
                renderedItem.focus();
            }

            this._renderedItems.push(renderedItem);
        }

        return element;
    }

    keyDown(e: KeyboardEvent) {
        super.keyDown(e);

        var selectedItemIndex = this._selectedIndex;

        switch (e.keyCode) {
            case Constants.KEY_TAB:
                this.close();

                break;
            /*
            case Constants.KEY_ENTER:
                if (this.selectedIndex >= 0) {
                    this.selectedIndex = this.selectedIndex;

                    this.close();
                }

                break;
            */
            case Constants.KEY_UP:
                if (selectedItemIndex <= 0) {
                    selectedItemIndex = this._renderedItems.length - 1;
                }
                else {
                    selectedItemIndex--;

                    if (selectedItemIndex < 0) {
                        selectedItemIndex = this._renderedItems.length - 1;
                    }
                }

                this.selectedIndex = selectedItemIndex;

                e.cancelBubble = true;

                break;
            case Constants.KEY_DOWN:
                if (selectedItemIndex < 0) {
                    selectedItemIndex = 0;
                }
                else {
                    selectedItemIndex++;

                    if (selectedItemIndex >= this._renderedItems.length) {
                        selectedItemIndex = 0;
                    }
                }

                this.selectedIndex = selectedItemIndex;

                e.cancelBubble = true;

                break;
        }
    }

    popup(rootElement: HTMLElement) {
        if (!this._isOpen) {
            this._overlayElement = document.createElement("div");
            this._overlayElement.className = "ms-ctrl-overlay";
            this._overlayElement.tabIndex = 0;
            this._overlayElement.style.width = document.documentElement.scrollWidth + "px";
            this._overlayElement.style.height = document.documentElement.scrollHeight + "px";
            this._overlayElement.onfocus = (e) => { this.closePopup(); };

            document.body.appendChild(this._overlayElement);

            var rootElementBounds = rootElement.getBoundingClientRect();

            this._popupControlElement = this.render(rootElementBounds);
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
                var maxPopupHeight = window.innerHeight;

                this._popupControlElement.style.maxHeight = maxPopupHeight + "px";

                if (maxPopupHeight < popupElementBounds.height) {
                    top = Utils.getScrollY();
                }
                else {
                    top = Utils.getScrollY() + rootElementBounds.top + (rootElementBounds.height - maxPopupHeight) /2;
                }

                var availableSpaceRight = window.innerWidth - rootElementBounds.right;
                var availableSpaceLeft = rootElementBounds.left;

                if (availableSpaceLeft < popupElementBounds.width && availableSpaceRight < popupElementBounds.width) {
                    // Not enough space left or right of root element
                    var maxPopupWidth = window.innerWidth;

                    this._popupControlElement.style.maxWidth = maxPopupWidth + "px";

                    if (maxPopupWidth < popupElementBounds.width) {
                        left = Utils.getScrollX();
                    }
                    else {
                        left = Utils.getScrollX() + rootElementBounds.left + (rootElementBounds.width - maxPopupWidth) /2;
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

    get items(): Collection<DropDownItem> {
        return this._items;
    }

    get selectedIndex(): number {
        return this._selectedIndex;
    }

    set selectedIndex(index: number) {
        if (index >= 0 && index < this._renderedItems.length) {
            this._renderedItems[index].focus();

            this._selectedIndex = index;
        }
    }
}
