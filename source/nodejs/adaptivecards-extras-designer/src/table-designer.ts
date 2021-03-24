import { ContainerPeer, DesignerPeer, TypedCardElementPeer } from "adaptivecards-designer";
import { Table, TableRow } from "adaptivecards-extras";

export class TableCellPeer extends ContainerPeer { }

export class TableRowPeer extends TypedCardElementPeer<TableRow> {
    protected isContainer(): boolean {
        return true;
    }
}

export class TablePeer extends TypedCardElementPeer<Table> {
    protected isContainer(): boolean {
        return true;
    }
    
    canDrop(peer: DesignerPeer) {
        return true;
    }
}