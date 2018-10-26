import * as Constants from "./constants";
import { Collection } from "./collection";
import { InputWithPopup, PopupControl } from "./inputwithpopup";
export class DropDownItem {
    click() {
        if (this.onClick) {
            this.onClick(this);
        }
    }
    constructor(key, value) {
        this.key = key;
        this._value = value;
    }
    toString() {
        return this.value;
    }
    render() {
        if (!this._element) {
            this._element = document.createElement("span");
            this._element.className = "ms-ctrl ms-ctrl-dropdown-item";
            this._element.innerText = this.value;
            this._element.onmouseup = (e) => { this.click(); };
        }
        return this._element;
    }
    get value() {
        return this._value;
    }
    set value(newValue) {
        this._value = newValue;
        if (this._element) {
            this._element.innerText = newValue;
        }
    }
}
export class DropDownPopupControl extends PopupControl {
    constructor(owner) {
        super();
        this._renderedItems = [];
        this._selectedIndex = -1;
        this._owner = owner;
    }
    renderContent() {
        var element = document.createElement("div");
        element.className = "ms-ctrl ms-popup";
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
    keyDown(e) {
        super.keyDown(e);
        var selectedItemIndex = this._selectedIndex;
        switch (e.keyCode) {
            case Constants.KEY_TAB:
                this.close();
                break;
            case Constants.KEY_ENTER:
                if (this.selectedIndex >= 0) {
                    this._owner.selectedIndex = this.selectedIndex;
                    this.close();
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
    render(rootElementBounds) {
        var renderedElement = super.render(rootElementBounds);
        renderedElement.style.minWidth = (rootElementBounds.width / 2) + "px";
        renderedElement.style.maxWidth = rootElementBounds.width + "px";
        return renderedElement;
    }
    get selectedIndex() {
        return this._selectedIndex;
    }
    set selectedIndex(index) {
        if (index >= 0 && index < this._renderedItems.length) {
            this._renderedItems[index].focus();
            this._selectedIndex = index;
        }
    }
}
export class DropDown extends InputWithPopup {
    itemClicked(item) {
        this.selectedItem = item;
        this.closePopup();
        this.rootElement.focus();
    }
    validateRootElement(rootElement) {
        if (!(rootElement instanceof HTMLDivElement)) {
            throw new Error("DropDown requires a DIV element as its root.");
        }
    }
    createPopupControl() {
        return new DropDownPopupControl(this);
    }
    getCssClassName() {
        return "ms-ctrl ms-ctrl-dropdown";
    }
    constructor() {
        super();
        this._items = new Collection();
        this._items.onItemAdded = (item) => { item.onClick = (clickedItem) => { this.itemClicked(clickedItem); }; };
        this._items.onItemRemoved = (item) => { item.onClick = null; };
    }
    attach(rootElement) {
        super.attach(rootElement);
        for (var i = 0; i < this.rootElement.children.length; i++) {
            var childElement = this.rootElement.children[i];
            if (childElement.tagName.toLowerCase() == "ms-dropdown-item") {
                var item = new DropDownItem(childElement.attributes.getNamedItem("key").value, childElement.attributes.getNamedItem("value").value);
                this._items.add(item);
            }
        }
    }
    popup() {
        super.popup();
        this.popupControl.selectedIndex = this.selectedIndex;
    }
    get items() {
        return this._items;
    }
    get selectedItem() {
        return this.value;
    }
    set selectedItem(newValue) {
        this.value = newValue;
    }
    get selectedIndex() {
        return this.items.indexOf(this.value);
    }
    set selectedIndex(index) {
        if (index >= 0 && this.items.length > index) {
            this.selectedItem = this.items.get(index);
        }
    }
}
//# sourceMappingURL=dropdown.js.map