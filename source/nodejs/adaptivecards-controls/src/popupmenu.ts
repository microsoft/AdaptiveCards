// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Constants } from "./constants";
import { Collection } from "./collection";
import { PopupControl } from "./inputwithpopup";
import { DropDownItem } from "./dropdown";

export class PopupMenu extends PopupControl {
    private _items: Collection<DropDownItem> = new Collection<DropDownItem>();
    private _renderedItems: Array<HTMLElement> = [];
    private _selectedIndex: number = -1;

    constructor() {
        super();
    }

    protected renderContent(): HTMLElement {
        var element = document.createElement("div");
        element.className = "ms-ctrl ms-popup";
        element.setAttribute("role", "listbox");

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

        switch (e.key) {
            case Constants.keys.tab:
                this.closePopup(true);

                break;
            /*
            case Constants.keys.enter:
                if (this.selectedIndex >= 0) {
                    this.selectedIndex = this.selectedIndex;

                    this.close();
                }

                break;
            */
            case Constants.keys.up:
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
            case Constants.keys.down:
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
