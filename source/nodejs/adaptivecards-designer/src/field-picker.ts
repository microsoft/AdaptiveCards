// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Controls from "adaptivecards-controls";
import { FieldDefinition } from "./data";
import { TreeView } from "./tree-view";
import { DataTreeItem } from "./data-treeitem";

export class FieldPicker extends Controls.PopupControl {
    private _selectedField: FieldDefinition;

    protected renderContent(): HTMLElement {
        let element = document.createElement("div");
        element.className = "acd-fieldPicker-host";

        let treeItem = new DataTreeItem(this.dataStructure);

        let treeView = new TreeView(treeItem);
        treeView.onSelectedItemChanged = (sender) => {
            this._selectedField = (treeView.selectedItem as DataTreeItem).field;

            if (this._selectedField) {
                this.closePopup(false);
            }
        }

        element.appendChild(treeView.render());

        return element;
    }

    constructor(readonly dataStructure: FieldDefinition) {
        super();
    }

    keyDown(e: KeyboardEvent) {
        super.keyDown(e);

        // TODO
    }

    get selectedField(): FieldDefinition {
        return this._selectedField;
    }
}
