import { BaseTreeItem } from "./base-tree-item";
import * as Data from "./data";

export class DataTreeItem extends BaseTreeItem {
    protected getChildCount(): number {
        let properties = this.dataType.getProperties();

        if (properties) {
            return Object.keys(properties).length;
        }
        else {
            return 0;
        }
    }

    protected getLabelText(): string {
        return this.dataType.label;
    }

    protected renderChild(childIndex: number): HTMLElement {
        let properties = this.dataType.getProperties();

        if (properties) {
            let keys = Object.keys(properties);

            if (childIndex >= 0 && childIndex < keys.length) {
                let treeItem = new DataTreeItem(properties[keys[childIndex]]);

                return treeItem.render();
            }
            else {
                throw new Error("Index out of range: " + childIndex);
            }
        }

        throw new Error("This item has no children.");
    }

    protected getAdditionalText(): string {
        return this.dataType.getTypeName();
    }

    protected getAdditionalTextClass(): string {
        return "acd-data-tree-item-additionalText";
    }

    readonly dataType: Data.DataType;

    constructor(dataType: Data.DataType) {
        super();

        this.dataType = dataType;

        this._level = 0;

        let currentDataType = dataType;

        while (currentDataType) {
            this._level++;

            currentDataType = currentDataType.parent;
        }
    }
}