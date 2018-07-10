import { DesignerPeer } from "../card-designer";
import * as Utils from "../utils";

export default class TreeItem {
    readonly owner: DesignerPeer;
    private _listElement: HTMLElement;
    private _childContainerElement: HTMLElement;
    private _isExpanded: boolean = true;

    constructor(owner: DesignerPeer) {
        this.owner = owner;
    }

    render(indentationLevel: number = 0): HTMLElement {
        let rootElement = document.createElement("div");
        rootElement.className = "treeview__container";

        this._listElement = this.internalRender(indentationLevel);
        rootElement.appendChild(this._listElement);

        if (this.owner.getChildCount() > 0) {
            rootElement.appendChild(this.renderChildList(indentationLevel));
        }

        this.updateLayout();
        return rootElement;
    }

    private renderChildList(indentationLevel: number): HTMLElement {
        this._childContainerElement = document.createElement("div");
        this._childContainerElement.className = "treeview__container";

        for (let i = 0; i < this.owner.getChildCount(); i++) {
            let currentItem = this.owner.getChildAt(i);
            this._childContainerElement.appendChild(currentItem.treeItem.render(indentationLevel + 1));
        }

        if (!this._isExpanded) {
            this._childContainerElement.classList.add("is-folded");
        }

        return this._childContainerElement;
    }

    private internalRender (indentationLevel: number): HTMLElement {
        let listItem = document.createElement("div");
        listItem.className = "treeview__element";

        listItem.onclick = (e: MouseEvent) => {
            this.owner.isSelected = true;

            e.cancelBubble = true;
            e.preventDefault();
        }

        if (this.owner.getChildCount() > 0) {
            let foldArrow = document.createElement("button");
            foldArrow.onclick = (e: MouseEvent) => {
                e.cancelBubble = true;
                e.preventDefault();
                foldArrow.classList.toggle("is-rotated");
                this.foldTreeViewContainer();
            }

            foldArrow.className = `treeview__icon treeview__icon--arrow ${!this._isExpanded ? "is-rotated" : ""}`;
            listItem.appendChild(foldArrow);
        }

        let icon = document.createElement("span");
        icon.className = `treeview__icon treeview__icon--${Utils.sanitizeString(this.owner.getCardObjectTypeName())}`;
        listItem.appendChild(icon);

        let title = document.createElement("span");
        title.className = `treeview__title`;
        title.textContent = this.owner.getCardObjectTypeName();
        listItem.appendChild(title);

        listItem.style.paddingLeft = `${indentationLevel * 20 + 24}px`;
        return listItem;
    }

    updateLayout(): void {
        if (this.owner.isSelected) {
            this._listElement.classList.add("is-selected");
        }
        else {
            this._listElement.classList.remove("is-selected");
        }
    }

    private foldTreeViewContainer(): void {
        this._isExpanded = !this._isExpanded;
        this._childContainerElement.classList.toggle("is-folded")
    }
}
