import { Container, property, SerializableObject, SerializableObjectCollectionProperty, SerializationContext,
    Strings, ValidationEvent, Versions, TypeErrorType, CardElement, CardElementContainer, PropertyBag, SizeAndUnit,
    CustomProperty, PropertyDefinition, BaseSerializationContext, SizeUnit } from "adaptivecards";

export class ColumnDefinition extends SerializableObject {
    //#region Schema

    static readonly widthProperty = new CustomProperty<SizeAndUnit>(
        Versions.v1_0,
        "width",
        (sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
            let result: SizeAndUnit = property.defaultValue;
            let value = source[property.name];
            let invalidWidth = false;

            if (typeof value === "number" && !isNaN(value)) {
                result = new SizeAndUnit(value, SizeUnit.Weight);
            }
            else if (typeof value === "string") {
                try {
                    result = SizeAndUnit.parse(value);
                }
                catch (e) {
                    invalidWidth = true;
                }
            }
            else {
                invalidWidth = true;
            }

            if (invalidWidth) {
                context.logParseEvent(
                    sender,
                    ValidationEvent.InvalidPropertyValue,
                    Strings.errors.invalidColumnWidth(value));
            }

            return result;
        },
        (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: SizeAndUnit, context: BaseSerializationContext) => {
            if (value.unit === SizeUnit.Pixel) {
                context.serializeValue(target, "width", value.physicalSize + "px");
            }
            else {
                context.serializeNumber(target, "width", value.physicalSize);
            }
        },
        new SizeAndUnit(1, SizeUnit.Weight));

    @property(ColumnDefinition.widthProperty)
    width: SizeAndUnit = new SizeAndUnit(1, SizeUnit.Weight);


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

    protected internalToJSON(target: PropertyBag, context: SerializationContext) {
        super.internalToJSON(target, context);

        context.serializeArray(target, this.getCollectionPropertyName(), this._items);
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
            td.style.border = "1px solid red";
            td.style.verticalAlign = "top";
            td.appendChild(element);

            return td;
        }

        return undefined;
    }

    protected shouldSerialize(context: SerializationContext): boolean {
        return true;
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
        element.style.border = "1px solid red";

        while (this.getItemCount() < this.parentTable.getColumnCount()) {
            let cell = new TableCell();

            this.internalAddItem(cell);
        }

        for (let i = 0; i < this.getItemCount(); i++) {
            let renderedCell = this.getItemAt(i).render();

            if (renderedCell) {
                element.appendChild(renderedCell);
            }
        }

        return element.children.length > 0 ? element : undefined;
    }

    protected shouldSerialize(context: SerializationContext): boolean {
        return true;
    }

    getJsonTypeName(): string {
        return "TableRow";
    }

    removeItem(item: TableCell): boolean {
        return false;
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
            let totalWeights: number = 0;

            for (let column of this._columns) {
                if (column.width.unit === SizeUnit.Weight) {
                    totalWeights += column.width.physicalSize;
                }
            }

            let colGroup = document.createElement("colgroup");

            for (let column of this._columns) {
                let col = document.createElement("col");

                if (column.width.unit === SizeUnit.Pixel) {
                    col.style.width = column.width.physicalSize + "px";
                }
                else {
                    col.style.width = (100 / totalWeights * column.width.physicalSize) + "%";
                }

                colGroup.appendChild(col);
            }

            let element = document.createElement("table");
            // Layout must be fixed and width must be 100%, otherwise cells will not
            // shrink below the width of their content
            element.style.tableLayout = "fixed";
            element.style.width = "100%";
            element.style.borderCollapse = "collapse";
            element.style.border = "1px solid red";

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

    addColumn(column: ColumnDefinition) {
        this._columns.push(column);
    }

    getColumnCount(): number {
        return this._columns.length;
    }

    addRow(row: TableRow) {
        this.internalAddItem(row);
    }

    getJsonTypeName(): string {
        return "Table";
    }
}