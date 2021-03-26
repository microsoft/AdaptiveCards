import { Versions, VerticalAlignment } from "adaptivecards";
import { BooleanPropertyEditor, CardDesignerSurface, ContainerPeer, ContainerStylePropertyEditor, DesignContext,
    EnumPropertyEditor, NumberPropertyEditor, PeerCommand, PropertySheet, PropertySheetCategory,
    TypedCardElementPeer } from "adaptivecards-designer";
import { ColumnDefinition, Table, TableRow } from "adaptivecards-extras";

export class TableCellPeer extends ContainerPeer {
    canBeRemoved(): boolean {
        return false;
    }

    isDraggable(): boolean {
        return false;
    }
}

export class TableRowPeer extends TypedCardElementPeer<TableRow> {
    protected isContainer(): boolean {
        return true;
    }

    isDraggable(): boolean {
        return false;
    }
    
    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(PropertySheetCategory.StyleCategory, ContainerPeer.styleProperty);
    }
}

export class TablePeer extends TypedCardElementPeer<Table> {
    static readonly firstRowAsHeadersProperty = new BooleanPropertyEditor(
        Versions.v1_0,
        "firstRowAsHeaders",
        "First row as headers");

    static readonly cellSpacingProperty = new NumberPropertyEditor(
        Versions.v1_0,
        "cellSpacing",
        "Cell spacing (in pixels)");

    static readonly showGridLinesProperty = new BooleanPropertyEditor(
        Versions.v1_0,
        "showGridLines",
        "Grid lines");

    static readonly gridStyleProperty = new ContainerStylePropertyEditor(Versions.v1_0, "gridStyle", "Grid style");

    static readonly verticalCellContentAlignmentProperty = new EnumPropertyEditor(
        Versions.v1_0,
        "verticalCellContentAlignment",
        "Cell vertical content alignment",
        VerticalAlignment);

    protected isContainer(): boolean {
        return true;
    }

    initializeCardElement() {
        super.initializeCardElement();

        this.cardElement.addColumn(new ColumnDefinition());
        this.cardElement.addColumn(new ColumnDefinition());
        this.cardElement.addColumn(new ColumnDefinition());

        this.cardElement.addRow(new TableRow());
        this.cardElement.addRow(new TableRow());
        this.cardElement.addRow(new TableRow());
    }
    
    protected internalAddCommands(context: DesignContext, commands: Array<PeerCommand>) {
        super.internalAddCommands(context, commands);

        commands.push(
            new PeerCommand(
                {
                    name: "Add a row",
                    isPromotable: false,
                    execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                        let row = new TableRow();

                        this.cardElement.addRow(row);

                        this.insertChild(CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(this.designerSurface, this, row));
                    }
                })
        );
    }
    
    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(defaultCategory, TablePeer.firstRowAsHeadersProperty);

        propertySheet.add(
            PropertySheetCategory.StyleCategory,
            TablePeer.showGridLinesProperty,
            TablePeer.gridStyleProperty);

        propertySheet.add(PropertySheetCategory.LayoutCategory,
            TablePeer.cellSpacingProperty,
            TablePeer.verticalCellContentAlignmentProperty);
    }
}