// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Constants from "./constants";
import { Collection } from "./collection";
import { InputWithPopup, PopupControl } from "./inputwithpopup";

export class DropDownItem {
    private _element: HTMLElement;
    private _value: string;

    private click() {
        if (this.onClick) {
            this.onClick(this);
        }
    }

    readonly key: string;

    onClick: (item: DropDownItem) => void;

    constructor(key: string, value: string) {
        this.key = key;
        this._value = value;
    }

    toString(): string {
        return this.value;
    }

    render(): HTMLElement {
        if (!this._element) {
            this._element = document.createElement("span");
            this._element.className = "ms-ctrl ms-ctrl-dropdown-item";
            this._element.innerText = this.value;
            this._element.setAttribute("role", "option");
            this._element.setAttribute("aria-selected", "false");
            this._element.onmouseup = (e) => { this.click(); };
            this._element.onkeydown = (e) => {
                if (e.keyCode === Constants.KEY_ENTER) {
                    this.click();
                    e.cancelBubble = true;
                }
            };
        }

        return this._element;
    }

    get value(): string {
        return this._value;
    }

    set value(newValue: string) {
        this._value = newValue;

        if (this._element) {
            this._element.innerText = newValue;
        }
    }
}

export class DropDownPopupControl extends PopupControl {
    private _owner: DropDown;
    private _renderedItems: Array<HTMLElement> = [];
    private _selectedIndex: number = -1;

    constructor(owner: DropDown) {
        super();

        this._owner = owner;
    }

    protected renderContent(): HTMLElement {
        var element = document.createElement("div");
        element.className = "ms-ctrl ms-popup";
        element.setAttribute("role", "listbox");

        var selectedIndex = this._owner.selectedIndex;

        for (var i = 0; i < this._owner.items.length; i++) {
            var renderedItem = this._owner.items.get(i).render();
            renderedItem.tabIndex = 0;

            element.appendChild(renderedItem);

            if (i == selectedIndex) {
                renderedItem.focus();
            }

            this._renderedItems.push(renderedItem);
        }

        return element;
    }

    keyDown(e: KeyboardEvent) {
        super.keyDown(e); // handles ESC

        var selectedItemIndex = this._selectedIndex;

        switch (e.keyCode) {
            case Constants.KEY_TAB:
                this.closePopup(true);

                break;
            case Constants.KEY_ENTER:
                if (this.selectedIndex >= 0) {
                    this._owner.selectedIndex = this.selectedIndex;

                    this.closePopup(false);
                }

                break;
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

    render(rootElementBounds: ClientRect) {
        var renderedElement = super.render(rootElementBounds);

        renderedElement.style.minWidth = (rootElementBounds.width / 2) + "px";

        return renderedElement;
    }

    get selectedIndex(): number {
        return this._selectedIndex;
    }

    set selectedIndex(index: number) {
        if (index >= 0 && index < this._renderedItems.length) {
            // deselect previous item (if one was selected)
            if (this._selectedIndex >= 0 && this._selectedIndex < this._renderedItems.length) {
                this._renderedItems[this._selectedIndex].setAttribute("aria-selected", "false");
            }

            // select new item
            this._renderedItems[index].focus();
            this._renderedItems[index].setAttribute("aria-selected", "true");

            this._selectedIndex = index;
        }
    }
}

export class DropDown extends InputWithPopup<DropDownPopupControl, DropDownItem> {
    private _items: Collection<DropDownItem>;
    private _parentLabelId: string; // tracks the id of the parent control's label

    private itemClicked(item: DropDownItem) {
        this.selectedItem = item;
        this.closePopup(false);

        this.rootElement.focus();
    }

    protected validateRootElement(rootElement: HTMLElement) {
        if (!(rootElement instanceof HTMLDivElement)) {
            throw new Error("DropDown requires a DIV element as its root.");
        }
    }

    protected createPopupControl(): DropDownPopupControl {
        return new DropDownPopupControl(this);
    }

    protected getCssClassName(): string {
        return "ms-ctrl ms-ctrl-dropdown";
    }

    constructor() {
        super();

        this._items = new Collection<DropDownItem>();
        this._items.onItemAdded = (item) => { item.onClick = (clickedItem) => { this.itemClicked(clickedItem); }; }
        this._items.onItemRemoved = (item) => { item.onClick = null; }
    }

    attach(rootElement: HTMLElement) {
        super.attach(rootElement);

        for (var i = 0; i < this.rootElement.children.length; i++) {
            var childElement = this.rootElement.children[i];

            if (childElement.tagName.toLowerCase() == "ms-dropdown-item") {
                var item = new DropDownItem(
                    childElement.attributes.getNamedItem("key").value,
                    childElement.attributes.getNamedItem("value").value);

                this._items.add(item);
            }
        }

        // add aria-labelledby tag with all pertinent label ids
        let ariaLabelledByIds: Array<string> = [];

        if (this.parentLabelId) {
            ariaLabelledByIds.push(this.parentLabelId);
        }

        if (this.labelId) {
            ariaLabelledByIds.push(this.labelId);
        }

        if (ariaLabelledByIds.length > 0) {
            this.rootElement.setAttribute("aria-labelledby", ariaLabelledByIds.join(" "));
        }
    }

    popup() {
        super.popup();

        this.popupControl.selectedIndex = this.selectedIndex;
    }

    get items(): Collection<DropDownItem> {
        return this._items;
    }

    get selectedItem(): DropDownItem {
        return <DropDownItem>this.value;
    }

    set selectedItem(newValue: DropDownItem) {
        this.value = newValue;
    }

    get selectedIndex(): number {
        return this.items.indexOf(this.value);
    }

    set selectedIndex(index: number) {
        if (index >= 0 && this.items.length > index) {
            this.selectedItem = this.items.get(index);
        }
    }

    get parentLabelId() : string {
        return this._parentLabelId;
    }

    set parentLabelId(value: string) {
        this._parentLabelId = value;
    }
}
