import { Container, NumProperty, property, SerializableObject, SerializableObjectCollectionProperty, SerializationContext,
    StringProperty, Strings, ValidationEvent, Versions, TypeErrorType, CardElement, CardElementContainer } from "adaptivecards";

export class ColumnDefinition extends SerializableObject {
    //#region Schema

    static readonly headerProperty = new StringProperty(Versions.v1_0, "header", true);
    static readonly weightProperty = new NumProperty(Versions.v1_0, "weight", 1);

    @property(ColumnDefinition.headerProperty)
    header?: string;

    @property(ColumnDefinition.weightProperty)
    weight: number = 1;

    getSchemaKey(): string {
        return "ColumnDefinition";
    }

    //#endregion   
}

export abstract class TypedCardElementContainer<T extends CardElement> extends CardElementContainer {
    private _items: T[] = [];

    private parseItem(source: any, context: SerializationContext): T | undefined {
        return context.parseCardObject<T>(
            this,
            source,
            [], // Forbidden types not supported for elements for now
            !this.isDesignMode(),
            (typeName: string) => {
                return this.createItemInstance(typeName);
            },
            (typeName: string, errorType: TypeErrorType) => {
                context.logParseEvent(
                    undefined,
                    ValidationEvent.ElementTypeNotAllowed,
                    Strings.errors.elementTypeNotAllowed(typeName));
            });
    }

    protected abstract getCollectionPropertyName(): string;
    protected abstract createItemInstance(typeName: string): T | undefined;

    protected internalAddItem(item: T) {
        if (!item.parent) {
            this._items.push(item);

            item.setParent(this);
        }
        else {
            throw new Error(Strings.errors.elementAlreadyParented());
        }
    }

    protected internalRemoveItem(item: T): boolean {
        let itemIndex = this._items.indexOf(item);

        if (itemIndex >= 0) {
            this._items.splice(itemIndex, 1);

            item.setParent(undefined);

            this.updateLayout();

            return true;
        }

        return false;
    }

    protected internalParse(source: any, context: SerializationContext) {
        super.internalParse(source, context);

        this._items = [];

        let items = source[this.getCollectionPropertyName()];

        if (Array.isArray(items)) {
            for (let item of items) {
                let instance = this.parseItem(item, context);

                if (instance) {
                    this._items.push(instance);
                }
            }
        }
    }

    removeItem(item: T): boolean {
        return this.internalRemoveItem(item);
    }

    getItemCount(): number {
        return this._items.length;
    }

    getItemAt(index: number): T {
        return this._items[index];
    }

    getFirstVisibleRenderedItem(): T | undefined {
        return this.getItemCount() > 0 ? this.getItemAt(0) : undefined;
    }

    getLastVisibleRenderedItem(): T | undefined {
        return this.getItemCount() > 0 ? this.getItemAt(this.getItemCount() - 1) : undefined;
    }
}

export class TableCell extends Container {
    protected internalRender(): HTMLElement | undefined {
        let element = super.internalRender();

        if (element) {
            let td = document.createElement("td");
            td.appendChild(element);

            return td;
        }

        return undefined;
    }

    getJsonTypeName(): string {
        return "TableCell";
    }

    get isStandalone(): boolean {
        return false;
    }
}

export class TableRow extends TypedCardElementContainer<TableCell> {
    protected getCollectionPropertyName(): string {
        return "cells";
    }

    protected createItemInstance(typeName: string): TableCell | undefined {
        return !typeName || typeName === "TableCell" ? new TableCell() : undefined;
    }
    
    protected internalRender(): HTMLElement | undefined {
        let element = document.createElement("tr");

        while (this.getItemCount() < this.parentTable.getItemCount()) {
            let cell = new TableCell();

            this.internalAddItem(cell);
        }

        for (let i = 0; i < this.getItemCount(); i++) {
            let renderedCell = this.getItemAt(i).render();

            if (renderedCell) {
                element.appendChild(renderedCell);
            }
        }

        return element;
    }

    removeItem(item: TableCell): boolean {
        return false;
    }

    getJsonTypeName(): string {
        return "TableRow";
    }

    get parentTable(): Table {
        return this.parent as Table;
    }

    get isStandalone(): boolean {
        return false;
    }
}

export class Table extends TypedCardElementContainer<TableRow> {
    //#region Schema

    private static readonly columnsProperty = new SerializableObjectCollectionProperty(Versions.v1_0, "columns", ColumnDefinition);

    @property(Table.columnsProperty)
    private _columns: ColumnDefinition[] = [];

    //#endregion

    protected getCollectionPropertyName(): string {
        return "rows";
    }

    protected createItemInstance(typeName: string): TableRow | undefined {
        return !typeName || typeName === "TableRow" ? new TableRow() : undefined;
    }

    protected internalRender(): HTMLElement | undefined {
        if (this.getItemCount() > 0) {
            let totalColumnWeght: number = 0;

            for (let column of this._columns) {
                totalColumnWeght += column.weight;
            }

            let colGroup = document.createElement("colgroup");

            for (let column of this._columns) {
                let col = document.createElement("col");
                col.style.width = (100 / totalColumnWeght * column.weight) + "%";

                colGroup.appendChild(col);
            }

            let element = document.createElement("table");
            element.appendChild(colGroup);

            for (let i = 0; i < this.getItemCount(); i++) {
                let renderedRow = this.getItemAt(i).render();

                if (renderedRow) {
                    element.appendChild(renderedRow);
                }
            }

            return element;
        }

        return undefined;
    }

    addRow(row: TableRow) {
        this.internalAddItem(row);
    }

    getJsonTypeName(): string {
        return "Table";
    }
}