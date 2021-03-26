import { Container, property, SerializableObject, SerializableObjectCollectionProperty, SerializationContext,
    Strings, ValidationEvent, Versions, TypeErrorType, CardElement, StylableCardElementContainer, PropertyBag, SizeAndUnit,
    CustomProperty, PropertyDefinition, BaseSerializationContext, SizeUnit, BoolProperty, PaddingDefinition, Spacing,
    VerticalAlignment, EnumProperty, ContainerStyleProperty, stringToCssColor, NumProperty } from "adaptivecards";

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

export abstract class StylableContainer<T extends CardElement> extends StylableCardElementContainer {
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

export type CellType = "data" | "header";

export class TableCell extends Container {
    protected getHasBorder(): boolean {
        return this.parentTable.showGridLines;
    }

    protected applyBorder() {
        if (this.renderedElement && this.getHasBorder()) {
            let styleDefinition = this.hostConfig.containerStyles.getStyleByName(this.parentTable.gridStyle);

            if (styleDefinition.borderColor) {
                const borderColor = <string>stringToCssColor(styleDefinition.borderColor);

                if (borderColor) {
                    this.renderedElement.style.border = "1px solid " + borderColor;
                }
            }
        }
    }

    protected getDefaultPadding(): PaddingDefinition {
        return this.getHasBackground() || this.getHasBorder() ?
            new PaddingDefinition(
                Spacing.Small,
                Spacing.Small,
                Spacing.Small,
                Spacing.Small) : super.getDefaultPadding();
    }

    protected internalRender(): HTMLElement | undefined {
        let element = super.internalRender();

        if (element) {
            let cellElement = document.createElement(this.cellType === "data" ? "td" : "th");

            if (this.cellType === "header") {
                cellElement.setAttribute("scope", "col");
            }

            let verticalAlignment = this.parentTable.verticalCellContentAlignment ? this.parentTable.verticalCellContentAlignment : this.verticalContentAlignment;

            switch (verticalAlignment) {
                case VerticalAlignment.Center:
                    cellElement.style.verticalAlign = "center";
                    break;
                case VerticalAlignment.Bottom:
                    cellElement.style.verticalAlign = "bottom";
                    break;
                default:
                    cellElement.style.verticalAlign = "top";
                    break;                                
            }

            cellElement.appendChild(element);

            return cellElement;
        }

        return undefined;
    }

    protected shouldSerialize(context: SerializationContext): boolean {
        return true;
    }

    cellType: CellType = "data";

    getJsonTypeName(): string {
        return "TableCell";
    }

    get parentTable(): Table {
        return (this.parent as TableRow).parentTable;
    }

    get isStandalone(): boolean {
        return false;
    }
}

export class TableRow extends StylableContainer<TableCell> {
    //#region Schema

    static readonly styleProperty = new ContainerStyleProperty(Versions.v1_0, "style");

    @property(TableRow.styleProperty)
    get style(): string | undefined {
        let style = this.getValue(TableRow.styleProperty);

        if (style && this.hostConfig.containerStyles.getStyleByName(style)) {
            return style;
        }

        return undefined;
    }

    set style(value: string | undefined) {
        this.setValue(TableRow.styleProperty, value);
    }

    //#endregion

    protected applyBackground() {
        if (this.renderedElement) {
            let styleDefinition = this.hostConfig.containerStyles.getStyleByName(this.style, this.hostConfig.containerStyles.getStyleByName(this.defaultStyle));

            if (styleDefinition.backgroundColor) {
                const bgColor = <string>stringToCssColor(styleDefinition.backgroundColor);
                this.renderedElement.style.backgroundColor = bgColor;
            }
        }
    }

    protected getCollectionPropertyName(): string {
        return "cells";
    }

    protected createItemInstance(typeName: string): TableCell | undefined {
        return !typeName || typeName === "TableCell" ? new TableCell() : undefined;
    }
    
    protected internalRender(): HTMLElement | undefined {
        let rowElement = document.createElement("tr");

        /*
        while (this.getItemCount() < this.parentTable.getColumnCount()) {
            let cell = new TableCell();

            this.internalAddItem(cell);
        }
        */

        let isFirstRow = this.getIsFirstRow();

        for (let i = 0; i < this.getItemCount(); i++) {
            let cell = this.getItemAt(i);

            if (this.parentTable.firstRowAsHeaders && isFirstRow) {
                cell.cellType = "header";
            }

            let renderedCell = cell.render();

            if (renderedCell) {
                if (i > 0 && !this.parentTable.showGridLines && this.parentTable.cellSpacing > 0) {
                    renderedCell.style.paddingLeft = this.parentTable.cellSpacing + "px";
                }

                rowElement.appendChild(renderedCell);
            }
        }

        return rowElement.children.length > 0 ? rowElement : undefined;
    }

    protected shouldSerialize(context: SerializationContext): boolean {
        return true;
    }

    addCell(cell: TableCell) {
        this.internalAddItem(cell);
    }

    getJsonTypeName(): string {
        return "TableRow";
    }

    getIsFirstRow(): boolean {
        return this.parentTable.getItemAt(0) === this;
    }

    get parentTable(): Table {
        return this.parent as Table;
    }

    get isStandalone(): boolean {
        return false;
    }
}

export class Table extends StylableContainer<TableRow> {
    //#region Schema

    private static readonly columnsProperty = new SerializableObjectCollectionProperty(Versions.v1_0, "columns", ColumnDefinition);

    static readonly firstRowAsHeadersProperty = new BoolProperty(Versions.v1_0, "firstRowAsHeaders", true);
    static readonly cellSpacingProperty = new NumProperty(Versions.v1_0, "cellSpacing", 4);
    static readonly showGridLinesProperty = new BoolProperty(Versions.v1_0, "showGridLines", true);
    static readonly gridStyleProperty = new ContainerStyleProperty(Versions.v1_0, "gridStyle");
    static readonly verticalCellContentAlignmentProperty = new EnumProperty(Versions.v1_0, "verticalCellContentAlignment", VerticalAlignment);

    @property(Table.columnsProperty)
    private _columns: ColumnDefinition[] = [];

    @property(Table.cellSpacingProperty)
    cellSpacing: number = 4;

    @property(Table.firstRowAsHeadersProperty)
    firstRowAsHeaders: boolean = true;

    @property(Table.showGridLinesProperty)
    showGridLines: boolean = true;

    @property(Table.gridStyleProperty)
    get gridStyle(): string | undefined {
        let style = this.getValue(Table.gridStyleProperty);

        if (style && this.hostConfig.containerStyles.getStyleByName(style)) {
            return style;
        }

        return undefined;
    }

    set gridStyle(value: string | undefined) {
        this.setValue(Table.gridStyleProperty, value);
    }


    @property(Table.verticalCellContentAlignmentProperty)
    verticalCellContentAlignment?: VerticalAlignment;

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

            let tableElement = document.createElement("table");

            // Layout must be fixed and width must be 100%, otherwise cells will not
            // shrink below the width of their content
            tableElement.style.tableLayout = "fixed";
            tableElement.style.width = "100%";
            tableElement.style.borderCollapse = "collapse";

            tableElement.appendChild(colGroup);

            let tableBody = document.createElement("tbody");

            for (let i = 0; i < this.getItemCount(); i++) {
                let renderedRow = this.getItemAt(i).render();

                if (renderedRow) {
                    if (i > 0 && !this.showGridLines && this.cellSpacing > 0) {
                        let separatorRow = document.createElement("tr");
                        separatorRow.setAttribute("aria-hidden", "true");
                        separatorRow.style.height = this.cellSpacing + "px";

                        tableBody.appendChild(separatorRow);
                    }

                    if (i === 0) {
                        let theadElement = document.createElement("thead");
                        theadElement.appendChild(renderedRow);

                        tableElement.appendChild(theadElement);
                    }
                    else {
                        tableBody.appendChild(renderedRow);
                    }
                }
            }

            tableElement.appendChild(tableBody);

            return tableElement;
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

        while (row.getItemCount() < this.getColumnCount()) {
            row.addCell(new TableCell());
        }
    }

    getJsonTypeName(): string {
        return "Table";
    }
}