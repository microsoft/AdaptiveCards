import { DesignerPeer } from "./designer-peers";
export declare class TreeItem {
    private static collapsedIconClass;
    private static expandedIconClass;
    private _isExpanded;
    private _treeItemElement;
    private _expandCollapseElement;
    private _childContainerElement;
    readonly owner: DesignerPeer;
    constructor(owner: DesignerPeer);
    render(indentationLevel?: number): HTMLElement;
    updateLayout(): void;
    expand(): void;
}
