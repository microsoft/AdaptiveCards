// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Controls from "adaptivecards-controls";
import { FieldDefinition } from "./data";
import { TreeView } from "./tree-view";
import { DataTreeItem } from "./data-treeitem";

export class FieldPicker extends Controls.PopupControl {
    private _selectedField: FieldDefinition;
    private _treeView: TreeView;

    protected renderContent(): HTMLElement {
        let element = document.createElement("div");
        element.className = "acd-fieldPicker-host";

        let treeItem = new DataTreeItem(this.dataStructure);

        this._treeView = new TreeView(treeItem);

        this._treeView.onSelectedItemChanged = (sender) => {
            this._selectedField = (this._treeView.selectedItem as DataTreeItem).field;

            if (this._selectedField) {
                this.closePopup(false);
            }
        };

        element.appendChild(this._treeView.render());

        return element;
    }

    /**
     * @inheritdoc
     */
    render(rootElementBounds: ClientRect): HTMLElement {
        const rootElement = super.render(rootElementBounds);
        rootElement.tabIndex = -1;

        return rootElement;
    }

    constructor(readonly dataStructure: FieldDefinition) {
        super();
    }

    /**
     * @inheritdoc
     */
    focus() {
        if (this._treeView) {
            this._treeView.focus();
        }
    }

    keyDown(e: KeyboardEvent) {
        super.keyDown(e);

        // TODO
    }

    get selectedField(): FieldDefinition {
        return this._selectedField;
    }
}
