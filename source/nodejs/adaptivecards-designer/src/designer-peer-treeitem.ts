import { BaseTreeItem } from "./base-tree-item";
import { DesignerPeer } from "./designer-peers";

export class DesignerPeerTreeItem extends BaseTreeItem {
    private computeLevel() {
        this._level = 0;

        let peer = this.owner;

        while (peer) {
            this._level++;

            peer = peer.parent;
        }
    }

    protected getChildCount(): number {
        return this.owner.getChildCount();
    }

    protected getIconClass(): string {
        return this.owner.registration.iconClass;
    }

    protected getLabelText(): string {
        return this.owner.getCardObjectTypeName();
    }

    protected renderChild(childIndex: number): HTMLElement {
        return this.owner.getChildAt(childIndex).treeItem.render();
    }

    protected getAdditionalText(): string {
        return this.owner.getTreeItemText();
    }

    protected selected() {
        this.owner.isSelected = true;
    }

    readonly owner: DesignerPeer;

    constructor(owner: DesignerPeer) {
        super();

        this.owner = owner;
        this.owner.onParentChanged = (sender: DesignerPeer) => {
            this.computeLevel();
        }

        this.computeLevel();
    }

    updateLayout() {
        super.updateLayout();

        this.isSelected = this.owner.isSelected;
    }
}