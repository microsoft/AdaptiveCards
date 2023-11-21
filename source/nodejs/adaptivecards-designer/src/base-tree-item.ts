import { DraggableElement } from "./draggable-element";
import { Constants } from "adaptivecards-controls";
import { v4 as uuidv4 } from "uuid";

export abstract class BaseTreeItem extends DraggableElement {
    private static collapsedIconClass = "acd-icon-chevronRight";
    private static expandedIconClass = "acd-icon-chevronDown";

    private _isExpanded: boolean = true;
    private _isSelected: boolean = false;
    private _rootElement: HTMLElement;
    private _treeItemElement: HTMLElement;
    private _expandCollapseElement: HTMLElement;
    private _childContainerElement: HTMLElement;

    private needsToBeScrolled() {
        // detect the case where the treeViewHost's parent isn't currently
        // overflowed. if it *is* overflowed (has scrollbar), then scrolling is
        // appropriate. otherwise, we might be in a small-screen situation
        // (single column rendering) where scrolling is undesireable
        const treeViewHostParent = this._rootElement.closest(".acd-treeView-host").parentElement;
        return (treeViewHostParent && treeViewHostParent.scrollHeight > treeViewHostParent.clientHeight);
    }

    private setIsSelected(value: boolean, scrollIntoView: boolean) {
        if (this._isSelected !== value) {
            this._isSelected = value;

            if (this._isSelected) {
                this._treeItemElement.classList.add("selected");
            }
            else {
                this._treeItemElement.classList.remove("selected");
            }

            this._rootElement.setAttribute("aria-current", this._isSelected.toString());

            this.selectedChanged(scrollIntoView);
        }
    }

    protected abstract getLabelText(): string;

    protected click(e: MouseEvent) {
        super.click(e);

        this.setIsSelected(true, false);
    }

    protected getIconClass(): string {
        return null;
    }

    protected getAdditionalText(): string {
        return null;
    }

    protected getAdditionalTextClass(): string {
        return "acd-tree-item-additionalText";
    }

    protected getIndentationLevelIncrement(): number {
        return 8;
    }

    protected getDragSourceElement(): HTMLElement {
        return this._treeItemElement;
    }

    protected selectedChanged(scrollIntoView: boolean) {
        if (this.isSelected && scrollIntoView && this.needsToBeScrolled()) {
            this._rootElement.scrollIntoView();
        }

        if (this.onSelectedChange) {
            this.onSelectedChange(this);
        }
    }

    protected itemInvoked() {
        if (this.onItemInvoked) {
            this.onItemInvoked(this);
        }
    }

    private getExpandCollapseAriaText() : string {
        return (this._isExpanded ? "collapse" : "expand") + " " + this.getLabelText() + " element";
    }

    // collapse node or navigate to parent, if present
    private handleKeyboardLeftNav(): void {
        if (this._isExpanded && this.getChildCount() > 0) {
            // if we're an expanded node that has children, collapse the node.
            this._isExpanded = false;
            this.updateLayout();
            this._rootElement.tabIndex = 0;
            this._rootElement.focus();
        }
        else {
            // otherwise, we need to find the nearest ancestor treeitem or the root of the tree
            const nearestTreeItem = <HTMLElement>this._rootElement.parentElement.closest("[role='treeitem'], [role='tree']");
            const roleAttr = nearestTreeItem?.getAttribute("role");
            if (roleAttr === "treeitem") {
                nearestTreeItem.tabIndex = 0;
                nearestTreeItem.focus();
                this._rootElement.tabIndex = -1;
            }
            else if (roleAttr == "tree")
            {
                // only element higher up is the root DOM element of the tree, meaning `this`
                // represents the root node of the tree. set tabIndex so keyboard users can
                // tab back in.
                this._rootElement.tabIndex = 0;
                this._rootElement.focus();
            }
        }
    }

    // expand child nodes or navigate to first child, if present
    private handleKeyboardRightNav(): void {
        if (this.getChildCount() > 0) {
            if (this._isExpanded) {
                const childToFocus = <HTMLElement>this._childContainerElement.firstElementChild;
                childToFocus.tabIndex = 0;
                childToFocus.focus();
                this._rootElement.tabIndex = -1;
            }
            else {
                this._isExpanded = true;
                this.updateLayout();
            }
        }
    }

    protected internalRender(): HTMLElement {
        const hasChildren = (this.getChildCount() > 0);

        const labelId = uuidv4();

        this._rootElement = document.createElement("li");
        this._rootElement.style.paddingLeft = "0";
        this._rootElement.style.listStyleType = "none";
        this._rootElement.setAttribute("aria-labelledby", labelId);
        this._rootElement.setAttribute("aria-level", this._level.toString());
        this._rootElement.setAttribute("aria-current", this._isSelected.toString());
        this._rootElement.tabIndex = -1;

        if (hasChildren) {
            this._rootElement.setAttribute("aria-expanded", this._isExpanded.toString());
        }

        this._rootElement.setAttribute("role", "treeitem");
        this._rootElement.onclick = () => { this.click; };
        this._rootElement.onfocus = () => { this.setIsSelected(true, false); };
        this._rootElement.onkeydown = (e: KeyboardEvent) => {
            let handled = true;
            switch (e.key) {
                case Constants.keys.enter: {
                    this.itemInvoked();
                    break;
                }

                case Constants.keys.left: {
                    this.handleKeyboardLeftNav();
                    break;
                }

                case Constants.keys.right: {
                    this.handleKeyboardRightNav();
                    break;
                }

                default: {
                    handled = false;
                }
            }

            if (handled) {
                e.preventDefault();
                e.cancelBubble = true;
            }
        };

        this._treeItemElement = document.createElement("div");
        this._treeItemElement.classList.add("acd-tree-item");
        this._treeItemElement.style.display = "flex";
        this._treeItemElement.style.alignItems = "center";
        this._treeItemElement.style.paddingLeft = this.getIndentationLevelIncrement() * (1 + this.level) + "px";
        this._treeItemElement.classList.toggle("selected", this._isSelected);

        this._treeItemElement.setAttribute("aria-labelledby", labelId);

        this._expandCollapseElement = document.createElement("div");
        this._expandCollapseElement.classList.add("acd-tree-item-expandCollapseButton");
        this._expandCollapseElement.style.flex = "0 0 auto";
        this._expandCollapseElement.style.visibility = hasChildren ? "visible" : "hidden";
        this._expandCollapseElement.setAttribute("role", "button");
        this._expandCollapseElement.setAttribute("aria-label", this.getExpandCollapseAriaText());

        this._expandCollapseElement.onclick = (e: MouseEvent) => {
            this._isExpanded = !this._isExpanded;

            this.updateLayout();

            e.cancelBubble = true;
            e.preventDefault();
        }

        this._treeItemElement.appendChild(this._expandCollapseElement);

        let textElement = document.createElement("div");
        textElement.classList.add("acd-tree-item-text");
        textElement.style.flex = "1 1 auto";
        textElement.style.display = "flex";
        textElement.style.alignItems = "center";
        textElement.style.whiteSpace = "nowrap";
        textElement.style.textOverflow = "ellipsis";
        textElement.style.overflow = "hidden";
        textElement.style.marginRight = "8px";

        if (this.getIconClass()) {
            let iconElement = document.createElement("div");
            iconElement.classList.add("acd-icon", "acd-treeView-icon", this.getIconClass());

            textElement.appendChild(iconElement);
        }

        let labelSpan = document.createElement("span");
        labelSpan.classList.add("acd-tree-item-typeName");
        labelSpan.innerText = this.getLabelText();
        labelSpan.id = labelId;

        textElement.appendChild(labelSpan);

        let text = this.getAdditionalText();

        if (text && text != "") {
            let additionalTextSpan = document.createElement("span");
            additionalTextSpan.classList.add(this.getAdditionalTextClass());
            additionalTextSpan.innerText = " [" + text + "]";

            textElement.appendChild(additionalTextSpan);
        }

        this._treeItemElement.appendChild(textElement);

        this._rootElement.appendChild(this._treeItemElement);

        if (hasChildren) {
            this._childContainerElement = document.createElement("ul");
            this._childContainerElement.style.paddingLeft = "0";
            this._childContainerElement.style.listStyleType = "none";
            this._childContainerElement.setAttribute("role", "group");

            for (let i = 0; i < this.getChildCount(); i++) {
                let renderedChildItem = this.getChildAt(i).render();

                renderedChildItem.setAttribute("aria-posinset", (i+1).toString());
                renderedChildItem.setAttribute("aria-setsize", this.getChildCount().toString());

                this._childContainerElement.appendChild(renderedChildItem);
            }

            this._rootElement.appendChild(this._childContainerElement);
        }

        this.updateLayout();

        return this._rootElement;
    }

    protected _level: number = 0;

    onSelectedChange: (sender: BaseTreeItem) => void;

    onItemInvoked: (sender: BaseTreeItem) => void;

    constructor(isExpanded: boolean = true) {
        super();

        this._isExpanded = isExpanded;
    }

    abstract getChildCount(): number;
    abstract getChildAt(index: number): BaseTreeItem;

    updateLayout() {
        if (this.getChildCount() > 0) {
            this._rootElement.setAttribute("aria-expanded", this._isExpanded.toString());
            this._expandCollapseElement.setAttribute("aria-label", this.getExpandCollapseAriaText());
            this._expandCollapseElement.classList.toggle(BaseTreeItem.expandedIconClass, this._isExpanded);
            this._expandCollapseElement.classList.toggle(BaseTreeItem.collapsedIconClass, !this._isExpanded);
            this._childContainerElement?.classList.toggle("acd-hidden", !this._isExpanded);
        }
    }

    expand() {
        if (!this._isExpanded) {
            this._isExpanded = true;

            this.updateLayout();
        }
    }

    collpase() {
        if (this._isExpanded) {
            this._isExpanded = false;

            this.updateLayout();
        }
    }

    isDraggable(): boolean {
        return false;
    }

    get level(): number {
        return this._level;
    }

    get isSelected(): boolean {
        return this._isSelected;
    }

    set isSelected(value: boolean) {
        this.setIsSelected(value, true);
    }
}
