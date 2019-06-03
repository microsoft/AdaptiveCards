// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { DesignerPeer } from "./designer-peers";

export class TreeItem {
    private static collapsedIconClass = "acd-icon-chevronRight";
    private static expandedIconClass = "acd-icon-chevronDown";

    private _isExpanded: boolean = true;
    private _renderedElement: HTMLElement;
    private _treeItemElement: HTMLElement;
    private _expandCollapseElement: HTMLElement;
    private _childContainerElement: HTMLElement;

    readonly owner: DesignerPeer;

    constructor(owner: DesignerPeer) {
        this.owner = owner;
    }

    render(indentationLevel: number = 0): HTMLElement {
        this._renderedElement = document.createElement("div");

        this._treeItemElement = document.createElement("div");
        this._treeItemElement.classList.add("acd-tree-item");
        this._treeItemElement.style.display = "flex";
        this._treeItemElement.style.alignItems = "center";
        this._treeItemElement.style.paddingLeft = 8 + 8 * indentationLevel + "px";
        this._treeItemElement.onclick = (e: MouseEvent) => {
            this._isExpanded = !this._isExpanded;

            this.updateLayout();

            e.cancelBubble = true;
            e.preventDefault();
        }

        this._expandCollapseElement = document.createElement("div");
        this._expandCollapseElement.classList.add("acd-tree-item-expandCollapseButton");
        this._expandCollapseElement.style.flex = "0 0 auto";
        this._expandCollapseElement.style.visibility = this.owner.getChildCount() > 0 ? "visible" : "hidden";

        this._treeItemElement.appendChild(this._expandCollapseElement);

        let textElement = document.createElement("div");
        textElement.classList.add("acd-tree-item-text");
        textElement.style.flex = "1 1 auto";
        textElement.style.display = "flex";
        textElement.style.alignItems = "center";
        textElement.style.whiteSpace = "nowrap";
        textElement.style.textOverflow = "ellipsis";
        textElement.style.overflow = "hidden";
        textElement.onclick = (e: MouseEvent) => {
            this.owner.isSelected = true;

            e.cancelBubble = true;
            e.preventDefault();
        }

        let iconElement = document.createElement("div");
        iconElement.classList.add("acd-icon", this.owner.registration.iconClass);

        textElement.appendChild(iconElement);

        let typeNameSpan = document.createElement("span");
        typeNameSpan.classList.add("acd-tree-item-typeName");
        typeNameSpan.innerText = this.owner.getCardObject().getJsonTypeName();

        textElement.appendChild(typeNameSpan);

        let text = this.owner.getTreeItemText();

        if (text && text != "") {
            let additionalTextSpan = document.createElement("span");
            additionalTextSpan.classList.add("acd-tree-item-additionalText");
            additionalTextSpan.innerText = " [" + text + "]";

            textElement.appendChild(additionalTextSpan);
        }

        this._treeItemElement.appendChild(textElement);

        this._renderedElement.appendChild(this._treeItemElement);

        this._childContainerElement = document.createElement("div");

        for (let i = 0; i < this.owner.getChildCount(); i++) {
            let renderedChildItem = this.owner.getChildAt(i).treeItem.render(indentationLevel + 1);

            this._childContainerElement.appendChild(renderedChildItem);
        }

        this._renderedElement.appendChild(this._childContainerElement);

        this.updateLayout();

        return this._renderedElement;
    }

    updateLayout() {
        if (this._isExpanded) {
            this._childContainerElement.classList.remove("acd-hidden");
            this._expandCollapseElement.classList.remove(TreeItem.collapsedIconClass);
            this._expandCollapseElement.classList.add(TreeItem.expandedIconClass);
        }
        else {
            this._childContainerElement.classList.add("acd-hidden");
            this._expandCollapseElement.classList.add(TreeItem.collapsedIconClass);
            this._expandCollapseElement.classList.remove(TreeItem.expandedIconClass);
        }

        if (this.owner.isSelected) {
            this._treeItemElement.classList.add("selected");
        }
        else {
            this._treeItemElement.classList.remove("selected");
        }
    }

    expand() {
        this._isExpanded = true;

        this.updateLayout();
    }

    get renderedElement(): HTMLElement {
        return this._renderedElement;
    }
}
