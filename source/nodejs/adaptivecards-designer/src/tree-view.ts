// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { BaseTreeItem } from "./base-tree-item";
import { Constants } from "adaptivecards-controls";

export class TreeView {
    private _selectedItem: BaseTreeItem = undefined;

    private setupTreeItemEvents(treeItem: BaseTreeItem) {
        treeItem.onSelectedChange = (sender: BaseTreeItem) => {
            this.selectedItem = sender;
        };
        treeItem.onItemInvoked = (treeItem: BaseTreeItem) => {
            this.itemInvoked(treeItem);
        };

        for (let i = 0; i < treeItem.getChildCount(); i++) {
            this.setupTreeItemEvents(treeItem.getChildAt(i));
        }
    }

    private getVisibleTreeItems() : HTMLElement[] | null
    {
        // get all treeitem nodes in this view
        const treeItems = (<HTMLElement[]>Array.from(this.rootItem?.renderedElement?.querySelectorAll(":scope [role='treeitem']")));

        // filter out any hidden nodes (i.e. collapsed children). `[role='tree']` here is to prevent
        // looking outside of the tree.
        return treeItems?.filter((el) => !((<HTMLElement>el.parentElement.closest(".acd-hidden, [role='tree']"))?.classList.contains("acd-hidden")));
    }

    private static moveFocus(from: HTMLElement, to: HTMLElement): void
    {
        to.tabIndex = 0;
        to.focus();
        from.tabIndex = -1;
    }

    protected selectedItemChanged() {
        if (this.onSelectedItemChanged) {
            this.onSelectedItemChanged(this);
        }
    }

    protected itemInvoked(sender: BaseTreeItem) {
        if (this.onItemInvoked) {
            this.onItemInvoked(sender);
        }
    }

    focus() {
        this.rootItem?.focus();
    }

    render(): HTMLElement {
        let treeRoot = document.createElement("ul");
        treeRoot.style.paddingLeft = "0";
        treeRoot.style.listStyleType = "none";
        treeRoot.className = "acd-treeView";
        treeRoot.setAttribute("role", "tree");
        treeRoot.onkeydown = (e: KeyboardEvent) => {
            const currentElement = e.target as HTMLElement;
            let handled = true;
            switch (e.key) {
                case Constants.keys.up: {
                    const treeItems = this.getVisibleTreeItems();
                    const index = treeItems.findIndex((el) => el === currentElement);
                    if (index > 0) {
                        let nextElement = treeItems.at(index - 1);
                        TreeView.moveFocus(currentElement, nextElement);
                    }
                    else {
                        // on first child of tree root, so pressing up should focus the root
                        TreeView.moveFocus(currentElement, this.rootItem.renderedElement);
                    }

                    break;
                }

                case Constants.keys.down: {
                    const treeItems = this.getVisibleTreeItems();
                    const index = treeItems.findIndex((el) => el === currentElement);
                    if (index + 1 < treeItems.length) {
                        const nextElement = treeItems.at(index + 1);
                        TreeView.moveFocus(currentElement, nextElement);
                    }

                    break;
                }

                default: {
                    handled = false;
                }
            }

            if (handled) {
                e.cancelBubble = true;
                e.preventDefault();
            }
        };

        const rootItemElement = this.rootItem.render();
        rootItemElement.tabIndex = 0;
        treeRoot.appendChild(rootItemElement);

        this.setupTreeItemEvents(this.rootItem);

        return treeRoot;
    }

    onSelectedItemChanged: (sender: TreeView) => void;

    onItemInvoked: (item: BaseTreeItem) => void;

    constructor(readonly rootItem: BaseTreeItem) { }

    get selectedItem(): BaseTreeItem {
        return this._selectedItem;
    }

    set selectedItem(value: BaseTreeItem) {
        if (value !== this._selectedItem) {
            if (this._selectedItem) {
                this._selectedItem.isSelected = false;
            }

            this._selectedItem = value;

            if (this._selectedItem) {
                this._selectedItem.isSelected = true;
            }

            this.selectedItemChanged();
        }
    }
}
