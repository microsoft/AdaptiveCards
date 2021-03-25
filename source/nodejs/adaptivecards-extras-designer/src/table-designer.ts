import { Versions, VerticalAlignment } from "adaptivecards";
import { BooleanPropertyEditor, CardDesignerSurface, ContainerPeer, DesignContext, EnumPropertyEditor, PeerCommand, PropertySheet, PropertySheetCategory, TypedCardElementPeer } from "adaptivecards-designer";
import { ColumnDefinition, Table, TableRow } from "adaptivecards-extras";

export class TableCellPeer extends ContainerPeer { }

export class TableRowPeer extends TypedCardElementPeer<TableRow> {
    protected isContainer(): boolean {
        return true;
    }

    isDraggable(): boolean {
        return false;
    }
}

export class TablePeer extends TypedCardElementPeer<Table> {
    static readonly showGridLinesProperty = new BooleanPropertyEditor(
        Versions.v1_3,
        "showGridLines",
        "Grid lines");

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

        propertySheet.add(PropertySheetCategory.StyleCategory, TablePeer.showGridLinesProperty);
        propertySheet.add(PropertySheetCategory.LayoutCategory, TablePeer.verticalCellContentAlignmentProperty);
    }
}