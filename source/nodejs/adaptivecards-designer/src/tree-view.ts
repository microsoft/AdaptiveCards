// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { BaseTreeItem } from "./base-tree-item";

export class TreeView {
    private _selectedItem: BaseTreeItem = undefined;

    private setupTreeItemEvents(treeItem: BaseTreeItem) {
        treeItem.onSelectedChange = (sender: BaseTreeItem) => {
            this.selectedItem = sender;
        };

        for (let i = 0; i < treeItem.getChildCount(); i++) {
            this.setupTreeItemEvents(treeItem.getChildAt(i));
        }
    }

    protected selectedItemChanged() {
        if (this.onSelectedItemChanged) {
            this.onSelectedItemChanged(this);
        }
    }

    render(): HTMLElement {
        let treeRoot = document.createElement("div");
        treeRoot.className = "acd-treeView";
        treeRoot.tabIndex = 0;
        treeRoot.onkeyup = (e: KeyboardEvent) => {
            alert("key up");
        };
        treeRoot.appendChild(this.rootItem.render());

        this.setupTreeItemEvents(this.rootItem);

        return treeRoot;
    }

    onSelectedItemChanged: (sender: TreeView) => void;

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
