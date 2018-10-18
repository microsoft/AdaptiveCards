"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var TreeItem = /** @class */ (function () {
    function TreeItem(owner) {
        this._isExpanded = true;
        this.owner = owner;
    }
    TreeItem.prototype.render = function (indentationLevel) {
        var _this = this;
        if (indentationLevel === void 0) { indentationLevel = 0; }
        var rootElement = document.createElement("div");
        this._treeItemElement = document.createElement("div");
        this._treeItemElement.classList.add("acd-tree-item");
        this._treeItemElement.style.display = "flex";
        this._treeItemElement.style.alignItems = "center";
        this._treeItemElement.style.paddingLeft = 8 + 8 * indentationLevel + "px";
        this._treeItemElement.onclick = function (e) {
            _this._isExpanded = !_this._isExpanded;
            _this.updateLayout();
            e.cancelBubble = true;
            e.preventDefault();
        };
        this._expandCollapseElement = document.createElement("div");
        this._expandCollapseElement.classList.add("acd-tree-item-expandCollapseButton");
        this._expandCollapseElement.style.flex = "0 0 auto";
        this._expandCollapseElement.style.visibility = this.owner.getChildCount() > 0 ? "visible" : "hidden";
        this._treeItemElement.appendChild(this._expandCollapseElement);
        var textElement = document.createElement("div");
        textElement.classList.add("acd-tree-item-text");
        textElement.style.flex = "1 1 auto";
        textElement.style.display = "flex";
        textElement.style.alignItems = "center";
        textElement.style.whiteSpace = "nowrap";
        textElement.style.textOverflow = "ellipsis";
        textElement.style.overflow = "hidden";
        textElement.onclick = function (e) {
            _this.owner.isSelected = true;
            e.cancelBubble = true;
            e.preventDefault();
        };
        var iconElement = document.createElement("div");
        iconElement.classList.add("acd-icon", this.owner.registration.iconClass);
        textElement.appendChild(iconElement);
        var typeNameSpan = document.createElement("span");
        typeNameSpan.classList.add("acd-tree-item-typeName");
        typeNameSpan.innerText = this.owner.getCardObjectTypeName();
        textElement.appendChild(typeNameSpan);
        var text = this.owner.getTreeItemText();
        if (text && text != "") {
            var additionalTextSpan = document.createElement("span");
            additionalTextSpan.classList.add("acd-tree-item-additionalText");
            additionalTextSpan.innerText = " [" + text + "]";
            textElement.appendChild(additionalTextSpan);
        }
        this._treeItemElement.appendChild(textElement);
        rootElement.appendChild(this._treeItemElement);
        this._childContainerElement = document.createElement("div");
        for (var i = 0; i < this.owner.getChildCount(); i++) {
            var renderedChildItem = this.owner.getChildAt(i).treeItem.render(indentationLevel + 1);
            this._childContainerElement.appendChild(renderedChildItem);
        }
        rootElement.appendChild(this._childContainerElement);
        this.updateLayout();
        return rootElement;
    };
    TreeItem.prototype.updateLayout = function () {
        if (this._isExpanded) {
            this._childContainerElement.classList.remove("acd-hidden");
            this._expandCollapseElement.classList.remove(TreeItem.collapsedIconClass);
            this._expandCollapseElement.classList.add(TreeItem.expandedIconClass);
        }
        else {
            this._childContainerElement.classList.add("acd-hidden");
            this._expandCollapseElement.classList.add(TreeItem.collapsedIconClass);
            this._expandCollapseElement.classList.remove(TreeItem.expandedIconClass);
        }
        if (this.owner.isSelected) {
            this._treeItemElement.classList.add("selected");
        }
        else {
            this._treeItemElement.classList.remove("selected");
        }
    };
    TreeItem.prototype.expand = function () {
        this._isExpanded = true;
        this.updateLayout();
    };
    TreeItem.collapsedIconClass = "acd-icon-chevronRight";
    TreeItem.expandedIconClass = "acd-icon-chevronDown";
    return TreeItem;
}());
exports.TreeItem = TreeItem;
//# sourceMappingURL=treeitem.js.map