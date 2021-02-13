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

        for (let i = 0; i < this.getChildCount(); i++) {
            (this.getChildAt(i) as DesignerPeerTreeItem).computeLevel();
        }
    }

    protected getIconClass(): string {
        return this.owner.registration.iconClass;
    }

    protected getLabelText(): string {
        return this.owner.getCardObject().getJsonTypeName();
    }

    protected getAdditionalText(): string {
        return this.owner.getTreeItemText();
    }

    protected selectedChanged(scrollIntoView: boolean) {
        super.selectedChanged(scrollIntoView);

        this.owner.isSelected = this.isSelected;
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

    getChildCount(): number {
        return this.owner.getChildCount();
    }

    getChildAt(index: number): BaseTreeItem {
        return this.owner.getChildAt(index).treeItem;
    }
}
