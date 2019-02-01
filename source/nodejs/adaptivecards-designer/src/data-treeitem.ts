import { BaseTreeItem } from "./base-tree-item";
import * as Data from "./data";

export class DataTreeItem extends BaseTreeItem {
    private _children: Array<DataTreeItem> = null;

    private buildChildList() {
        if (!this._children) {
            this._children = [];

            let properties = this.dataType.getProperties();

            if (properties) {
                let keys = Object.keys(properties);

                for (let key of keys) {
                    this._children.push(new DataTreeItem(properties[key]));
                }
            }
        }
    }

    protected getLabelText(): string {
        return this.dataType.label;
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

    getChildCount(): number {
        this.buildChildList();

        return this._children.length;
    }

    getChildAt(index: number): DataTreeItem {
        this.buildChildList();
        
        return this._children[index];
    }
}