import { BaseTreeItem } from "./base-tree-item";
import * as Data from "./data";

export class DataTreeItem extends BaseTreeItem {
    private _children: Array<DataTreeItem> = null;

    private buildChildList() {
        if (!this._children) {
            this._children = [];

            let properties = this.field.children;

            if (properties) {
                let keys = Object.keys(properties);

                for (let key of keys) {
                    this._children.push(new DataTreeItem(properties[key]));
                }
            }
        }
    }

    protected getLabelText(): string {
        return this.field.name;
    }

    protected getAdditionalText(): string {
        return this.field.typeName;
    }

    protected getAdditionalTextClass(): string {
        return "acd-data-tree-item-additionalText";
    }

    readonly field: Data.FieldDefinition;

    constructor(field: Data.FieldDefinition) {
        super();

        this.field = field;

        this._level = 0;

        let currentField = field;

        while (currentField) {
            this._level++;

            currentField = currentField.parent;
        }
    }

    isDraggable(): boolean {
        return false;
    }

    getChildCount(): number {
        this.buildChildList();

        return this._children.length;
    }

    getChildAt(index: number): DataTreeItem {
        this.buildChildList();

        return this._children[index];
    }
}
