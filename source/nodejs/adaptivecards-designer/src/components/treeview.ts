import * as Adaptive from "adaptivecards";
import * as Designer from "../card-designer";
import * as Utils from "../utils"
import { AdaptiveCard } from "adaptivecards";

export default class Treeview {
    private _designer: Designer.CardDesigner;
    private _treeViewFoldedElements: Array<string>;

    public constructor() {
        this._treeViewFoldedElements = [];
    }

    public updateDesigner(designer: Designer.CardDesigner) {
        this._designer = designer;
        this.createTreeviewTitle();
    }

    public generateTreeViewElements(cardItems: Array<Adaptive.CardElement | Adaptive.Action>, peer: Designer.DesignerPeer, identationLevel: number = 0): HTMLElement {
        if (!cardItems || cardItems.length === 0) {
            let node = document.createElement("ul");
            return node;
        }

        let selected_id: string;
        if  (peer instanceof Designer.ActionPeer) {
            selected_id = peer ? peer.action.elementId : "";
        } else if(peer instanceof Designer.CardElementPeer) {
            selected_id = peer ? peer.cardElement.elementId : "";
        }

        let itemList = document.createElement("ul");
        itemList.className = "treeview__container";

        let itemIndex = 0;
        while(itemIndex < cardItems.length) {
            let item = cardItems[itemIndex];
            const listItem = this.createTreeViewListItem(item, selected_id, identationLevel);
            itemList.appendChild(listItem);

            const isFolded = this._treeViewFoldedElements.indexOf(item.elementId) !== -1;

            let childs = [];
            if ([Adaptive.Container.name, Adaptive.Column.name].indexOf(item.getJsonTypeName()) !== -1) {
                childs = (item as Adaptive.Container).getItems();
            } else if (item.getJsonTypeName() === Adaptive.ColumnSet.name) {
                childs = (item as Adaptive.ColumnSet).getColumns();
            }

            if (childs.length) {
                itemList.appendChild(this.createChildList(childs, peer, identationLevel, isFolded));
            } else {
                let emptyChild = document.createElement("li");
                emptyChild.className = "treeview__element is-empty";
                itemList.appendChild(emptyChild)
            }

            itemIndex++;
        }
        return itemList;
    }

    private createTreeviewTitle(): HTMLElement {
        const treeviewItems = document.querySelector(".js-treeview-items");
        let node = document.createElement("h2");
        let newtext = document.createTextNode("AdaptiveCard");
        node.className = "treeview__section-title";
        node.appendChild(newtext);
        treeviewItems.appendChild(node);
        return treeviewItems as HTMLElement;
    }

    private createChildList(items, peer, identationLevel, isFolded): HTMLElement {
        const newItem = document.createElement("li");
        newItem.className = "treeview__element";
        if (isFolded) {
            newItem.className += " is-folded";
        }

        newItem.appendChild(this.generateTreeViewElements(items, peer, ++identationLevel));
        return newItem;
    }

    private createTreeViewListItem (item: Adaptive.CardElement | Adaptive.Action, selected_id: string, identationLevel: number): HTMLElement {
        let listItem = document.createElement("li");
        listItem.className = "treeview__element";
        if (selected_id && item.elementId === selected_id) {
            listItem.className += " is-selected";
        }

        if ([Adaptive.Container.name, Adaptive.Column.name, Adaptive.ColumnSet.name].indexOf(item.getJsonTypeName()) !== -1) {
            let foldArrow = document.createElement("button");
            foldArrow.className = `btn treeview__icon treeview__icon--arrow`;
            if (this._treeViewFoldedElements.indexOf(item.elementId) !== -1) {
                foldArrow.classList.toggle("is-rotated");
            }
            foldArrow.addEventListener("click", () => {
                this.foldTreeViewContainer(item.elementId, foldArrow);
                foldArrow.classList.toggle("is-rotated");
            });
            listItem.appendChild(foldArrow);
        }

        let icon = document.createElement("span");
        icon.className = `treeview__icon treeview__icon--${Utils.sanitizeString(item.getJsonTypeName())}`;
        listItem.appendChild(icon);

        let title = document.createElement("span");
        title.className = `treeview__title`;
        title.textContent = item.getJsonTypeName();
        listItem.appendChild(title);

        listItem.addEventListener("click", () => {
            this._designer.setSelectedPeerById(item.elementId);
        });
        listItem.style.paddingLeft = `${identationLevel * 46 + 24}px`;
        return listItem;
    }

    private foldTreeViewContainer(elementId: string, listElement: HTMLElement) {
        const parent = listElement.parentElement;
        const childList = parent.nextElementSibling as HTMLElement;
        let addClassResult = childList.classList.toggle("is-folded")

        if (addClassResult) {
            this._treeViewFoldedElements.push(elementId);
        } else {
            let index = this._treeViewFoldedElements.indexOf(elementId);
            this._treeViewFoldedElements.splice(index, 1);
        }
    }
}
