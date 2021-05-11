// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { CardElement, StylableCardElementContainer, SerializationContext, Container, ContainerStyleProperty, StylableContainerBase } from "./card-elements";
import { HorizontalAlignment, VerticalAlignment, SizeUnit, ValidationEvent, TypeErrorType, Spacing } from "./enums";
import { TextStyleDefinition } from "./host-config";
import { BaseSerializationContext, BoolProperty, CustomProperty, EnumProperty, property,
    PropertyDefinition, SerializableObject, SerializableObjectCollectionProperty, Versions } from "./serialization";
import { PropertyBag, SizeAndUnit, PaddingDefinition } from "./shared";
import { Strings } from "./strings";
import { stringToCssColor } from "./utils";

export class ColumnDefinition extends SerializableObject {
    //#region Schema

    static readonly horizontalCellContentAlignmentProperty = new EnumProperty(Versions.v1_5, "horizontalCellContentAlignment", HorizontalAlignment);
    static readonly verticalCellContentAlignmentProperty = new EnumProperty(Versions.v1_5, "verticalCellContentAlignment", VerticalAlignment);

    static readonly widthProperty = new CustomProperty<SizeAndUnit>(
        Versions.v1_5,
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

    @property(ColumnDefinition.horizontalCellContentAlignmentProperty)
    horizontalCellContentAlignment?: HorizontalAlignment;

    @property(ColumnDefinition.verticalCellContentAlignmentProperty)
    verticalCellContentAlignment?: VerticalAlignment;

    @property(ColumnDefinition.widthProperty)
    width: SizeAndUnit = new SizeAndUnit(1, SizeUnit.Weight);

    getSchemaKey(): string {
        return "ColumnDefinition";
    }

    //#endregion

    computedWidth: SizeAndUnit;
}

export type CellType = "data" | "header";

export class TableCell extends Container {
    private _columnIndex: number = -1;
    private _cellType: CellType = "data";

    protected getHasBorder(): boolean {
        return this.parentRow.parentTable.showGridLines;
    }

    protected applyBorder() {
        if (this.renderedElement && this.getHasBorder()) {
            let styleDefinition = this.hostConfig.containerStyles.getStyleByName(this.parentRow.parentTable.gridStyle);

            if (styleDefinition.borderColor) {
                const borderColor = <string>stringToCssColor(styleDefinition.borderColor);

                if (borderColor) {
                    this.renderedElement.style.borderRight = "1px solid " + borderColor;
                    this.renderedElement.style.borderBottom = "1px solid " + borderColor;
                }
            }
        }
    }

    protected getDefaultPadding(): PaddingDefinition {
        return this.getHasBackground() || this.getHasBorder() || this.parentRow.getHasBackground() ?
            new PaddingDefinition(
                Spacing.Small,
                Spacing.Small,
                Spacing.Small,
                Spacing.Small) : super.getDefaultPadding();
    }

    protected adjustRenderedElementSize() {
        if (this.renderedElement) {
            let column = this.parentRow.parentTable.getColumnAt(this._columnIndex);

            if (column.computedWidth.unit === SizeUnit.Pixel) {
                this.renderedElement.style.flex = "0 0 " + column.computedWidth.physicalSize + "px";
            }
            else {
                this.renderedElement.style.flex = "1 1 " + column.computedWidth.physicalSize + "%";
            }
        }
    }

    protected internalRenderSeparator(): HTMLElement | undefined {
        let cellSpacing = this.hostConfig.table.cellSpacing;

        if (this._columnIndex > 0 && !this.parentRow.parentTable.showGridLines && cellSpacing > 0) {
            let separatorRow = document.createElement("div");
            separatorRow.setAttribute("aria-hidden", "true");
            separatorRow.style.width = cellSpacing + "px";

            return separatorRow;
        }

        return undefined;
    }

    protected internalRender(): HTMLElement | undefined {
        let cellElement = super.internalRender();

        if (cellElement) {
            cellElement.setAttribute("role", this.cellType === "data" ? "cell" : "columnheader");
            cellElement.style.minWidth = "0";

            if (this.cellType === "header") {
                cellElement.setAttribute("scope", "col");
            }

            let cellSpacing = this.hostConfig.table.cellSpacing;
    
            if (this._columnIndex > 0 && !this.parentRow.parentTable.showGridLines && cellSpacing > 0) {
                cellElement.style.marginLeft = cellSpacing + "px";
            }    
        }

        return cellElement;
    }

    protected shouldSerialize(context: SerializationContext): boolean {
        return true;
    }

    getJsonTypeName(): string {
        return "TableCell";
    }

    getEffectiveTextStyleDefinition(): TextStyleDefinition {
        if (this.cellType === "header") {
            return this.hostConfig.textStyles.columnHeader;
        }

        return super.getEffectiveTextStyleDefinition();
    }

    getEffectiveHorizontalAlignment(): HorizontalAlignment {
        if (this.horizontalAlignment !== undefined) {
            return this.horizontalAlignment;
        }

        if (this.parentRow.horizontalCellContentAlignment !== undefined) {
            return this.parentRow.horizontalCellContentAlignment;
        }

        if (this.columnIndex >= 0) {
            let horizontalAlignment = this.parentRow.parentTable.getColumnAt(this.columnIndex).horizontalCellContentAlignment;

            if (horizontalAlignment !== undefined) {
                return horizontalAlignment;
            }
        }

        if (this.parentRow.parentTable.horizontalCellContentAlignment !== undefined) {
            return this.parentRow.parentTable.horizontalCellContentAlignment;
        }

        return super.getEffectiveHorizontalAlignment();
    }

    getEffectiveVerticalContentAlignment(): VerticalAlignment {
        if (this.verticalContentAlignment !== undefined) {
            return this.verticalContentAlignment;
        }

        if (this.parentRow.verticalCellContentAlignment !== undefined) {
            return this.parentRow.verticalCellContentAlignment;
        }

        if (this.columnIndex >= 0) {
            let verticalAlignment = this.parentRow.parentTable.getColumnAt(this.columnIndex).verticalCellContentAlignment;

            if (verticalAlignment !== undefined) {
                return verticalAlignment;
            }
        }

        if (this.parentRow.parentTable.verticalCellContentAlignment !== undefined) {
            return this.parentRow.parentTable.verticalCellContentAlignment;
        }

        return super.getEffectiveVerticalContentAlignment();
    }

    get columnIndex(): number {
        return this._columnIndex;
    }

    get cellType(): CellType {
        return this._cellType;
    }

    get parentRow(): TableRow {
        return this.parent as TableRow;
    }

    get isStandalone(): boolean {
        return false;
    }
}

export class TableRow extends StylableContainerBase<TableCell> {
    //#region Schema

    static readonly styleProperty = new ContainerStyleProperty(Versions.v1_5, "style");
    static readonly horizontalCellContentAlignmentProperty = new EnumProperty(Versions.v1_5, "horizontalCellContentAlignment", HorizontalAlignment);
    static readonly verticalCellContentAlignmentProperty = new EnumProperty(Versions.v1_5, "verticalCellContentAlignment", VerticalAlignment);

    @property(TableRow.horizontalCellContentAlignmentProperty)
    horizontalCellContentAlignment?: HorizontalAlignment;

    @property(TableRow.verticalCellContentAlignmentProperty)
    verticalCellContentAlignment?: VerticalAlignment;

    //#endregion

    protected internalRenderSeparator(): HTMLElement | undefined {
        let cellSpacing = this.hostConfig.table.cellSpacing;

        if (this.parentTable.indexOf(this) > 0 && !this.parentTable.showGridLines && cellSpacing > 0) {
            let separatorRow = document.createElement("div");
            separatorRow.setAttribute("aria-hidden", "true");
            separatorRow.style.height = cellSpacing + "px";

            return separatorRow;
        }

        return undefined;
    }

    protected getDefaultPadding(): PaddingDefinition {
        return new PaddingDefinition(
            Spacing.None,
            Spacing.None,
            Spacing.None,
            Spacing.None);
    }

    protected applyBackground() {
        if (this.renderedElement) {
            let styleDefinition = this.hostConfig.containerStyles.getStyleByName(this.style, this.hostConfig.containerStyles.getStyleByName(this.defaultStyle));

            if (styleDefinition.backgroundColor) {
                const bgColor = <string>stringToCssColor(styleDefinition.backgroundColor);
                this.renderedElement.style.backgroundColor = bgColor;
            }
        }
    }

    protected createItemsHostElement(): HTMLElement {
        let element = document.createElement("div");
        element.setAttribute("role", "row");
        element.style.display = "flex";
        element.style.flexDirection = "row";

        return element;
    }

    protected getItemsCollectionPropertyName(): string {
        return "cells";
    }

    protected parseItem(context: SerializationContext, parent: CardElement | undefined, source: any, allowFallback: boolean): TableCell | undefined {
        return context.parseCardObject<TableCell>(
            this,
            source,
            [], // Forbidden types not supported for elements for now
            !this.isDesignMode(),
            (typeName: string) => {
                return !typeName || typeName === "TableCell" ? new TableCell() : undefined;
            },
            (typeName: string, errorType: TypeErrorType) => {
                context.logParseEvent(
                    undefined,
                    ValidationEvent.ElementTypeNotAllowed,
                    Strings.errors.elementTypeNotAllowed(typeName));
            });
    }
    
    protected internalRender(): HTMLElement | undefined {
        let isFirstRow = this.getIsFirstRow();

        for (let i = 0; i < Math.min(this.getItemCount(), this.parentTable.getColumnCount()); i++) {
            let cell = this.getItemAt(i);

            // Cheating a bit in order to keep cellType read-only
            cell["_columnIndex"] = i;
            cell["_cellType"] = (this.parentTable.firstRowAsHeaders && isFirstRow) ? "header" : "data";
        }

        return super.internalRender();
    }

    protected shouldSerialize(context: SerializationContext): boolean {
        return true;
    }

    addCell(cell: TableCell) {
        this.internalInsertItemAt(cell, this._items.length, true);
    }

    removeCellAt(columnIndex: number): boolean {
        if (columnIndex >= 0 && columnIndex < this.getItemCount()) {
            return this.removeItem(this.getItemAt(columnIndex));
        }

        return false;
    }

    ensureHasEnoughCells(cellCount: number) {
        while (this.getItemCount() < cellCount) {
            this.addCell(new TableCell());
        }
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

export class Table extends StylableContainerBase<TableRow> {
    //#region Schema

    private static readonly columnsProperty = new SerializableObjectCollectionProperty(Versions.v1_5, "columns", ColumnDefinition);

    static readonly firstRowAsHeadersProperty = new BoolProperty(Versions.v1_5, "firstRowAsHeaders", true);
    static readonly showGridLinesProperty = new BoolProperty(Versions.v1_5, "showGridLines", true);
    static readonly gridStyleProperty = new ContainerStyleProperty(Versions.v1_5, "gridStyle");
    static readonly horizontalCellContentAlignmentProperty = new EnumProperty(Versions.v1_5, "horizontalCellContentAlignment", HorizontalAlignment);
    static readonly verticalCellContentAlignmentProperty = new EnumProperty(Versions.v1_5, "verticalCellContentAlignment", VerticalAlignment);

    @property(Table.columnsProperty)
    private _columns: ColumnDefinition[] = [];

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

    @property(Table.horizontalCellContentAlignmentProperty)
    horizontalCellContentAlignment?: HorizontalAlignment;

    @property(Table.verticalCellContentAlignmentProperty)
    verticalCellContentAlignment?: VerticalAlignment;

    //#endregion

    private ensureRowsHaveEnoughCells() {
        for (let i = 0; i < this.getItemCount(); i++) {
            this.getItemAt(i).ensureHasEnoughCells(this.getColumnCount());
        }
    }

    private removeCellsFromColumn(columnIndex: number) {
        for (let i = 0; i < this.getItemCount(); i++) {
            this.getItemAt(i).removeCellAt(columnIndex);
        }
    }

    protected createItemsHostElement(): HTMLElement {
        let element = document.createElement("div");
        element.setAttribute("role", "table");
        element.style.display = "flex";
        element.style.flexDirection = "column";

        return element;
    }

    protected getItemsCollectionPropertyName(): string {
        return "rows";
    }

    protected parseItem(context: SerializationContext, parent: CardElement | undefined, source: any, allowFallback: boolean): TableRow | undefined {
        return context.parseCardObject<TableRow>(
            this,
            source,
            [], // Forbidden types not supported for elements for now
            !this.isDesignMode(),
            (typeName: string) => {
                return !typeName || typeName === "TableRow" ? new TableRow() : undefined;
            },
            (typeName: string, errorType: TypeErrorType) => {
                context.logParseEvent(
                    undefined,
                    ValidationEvent.ElementTypeNotAllowed,
                    Strings.errors.elementTypeNotAllowed(typeName));
            });
    }

    protected internalParse(source: PropertyBag, context: SerializationContext) {
        super.internalParse(source, context);

        this.ensureRowsHaveEnoughCells();
    }

    protected internalRender(): HTMLElement | undefined {
        if (this.getItemCount() > 0) {
            let totalWeights: number = 0;

            for (let column of this._columns) {
                if (column.width.unit === SizeUnit.Weight) {
                    totalWeights += column.width.physicalSize;
                }
            }

            for (let column of this._columns) {
                if (column.width.unit === SizeUnit.Pixel) {
                    column.computedWidth = new SizeAndUnit(column.width.physicalSize, SizeUnit.Pixel);
                }
                else {
                    column.computedWidth = new SizeAndUnit(100 / totalWeights * column.width.physicalSize, SizeUnit.Weight);
                }
            }

            let element = super.internalRender();

            if (element) {
                if (this.showGridLines) {
                    let styleDefinition = this.hostConfig.containerStyles.getStyleByName(this.gridStyle);

                    if (styleDefinition.borderColor) {
                        const borderColor = <string>stringToCssColor(styleDefinition.borderColor);
        
                        if (borderColor) {
                            element.style.borderTop = "1px solid " + borderColor;
                            element.style.borderLeft = "1px solid " + borderColor;
                        }
                    }
                }
            }

            return element;
        }

        return undefined;
    }

    addColumn(column: ColumnDefinition) {
        this._columns.push(column);

        this.ensureRowsHaveEnoughCells();
    }

    removeColumn(column: ColumnDefinition) {
        let index = this._columns.indexOf(column);

        if (index >= 0) {
            this.removeCellsFromColumn(index);

            this._columns.splice(index, 1);
        }
    }

    getColumnCount(): number {
        return this._columns.length;
    }

    getColumnAt(index: number): ColumnDefinition {
        return this._columns[index];
    }

    addRow(row: TableRow) {
        row.ensureHasEnoughCells(this.getColumnCount());
        
        this.internalInsertItemAt(row, this._items.length, true);
    }

    getJsonTypeName(): string {
        return "Table";
    }
}