import { CardDesignerSurface } from "adaptivecards-designer";
import { Table, TableCell, TableRow } from "adaptivecards-extras";
import { TableCellPeer, TablePeer, TableRowPeer } from "./table-designer";

export * from "./table-designer";

export function initializeDesignerSupport() {
    CardDesignerSurface.cardElementPeerRegistry.registerPeer(Table, TablePeer, "Extras");
    CardDesignerSurface.cardElementPeerRegistry.registerPeer(TableRow, TableRowPeer, "Extras");
    CardDesignerSurface.cardElementPeerRegistry.registerPeer(TableCell, TableCellPeer, "Extras");
}