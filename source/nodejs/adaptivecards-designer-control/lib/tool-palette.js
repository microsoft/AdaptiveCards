"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var DesignerSurface = require("./card-designer-surface");
var draggable_element_1 = require("./draggable-element");
var BasePaletteItem = /** @class */ (function (_super) {
    __extends(BasePaletteItem, _super);
    function BasePaletteItem() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    BasePaletteItem.prototype.internalRender = function () {
        var element = document.createElement("div");
        element.className = "acd-palette-item";
        element.style.display = "flex";
        var iconElement = document.createElement("div");
        iconElement.classList.add("acd-icon", this.getIconClass());
        iconElement.style.flex = "0 0 auto";
        var labelElement = document.createElement("div");
        labelElement.className = "acd-palette-item-label";
        labelElement.style.flex = "1 1 100%";
        labelElement.innerText = this.getText();
        element.appendChild(iconElement);
        element.appendChild(labelElement);
        return element;
    };
    BasePaletteItem.prototype.cloneElement = function () {
        return this.internalRender();
    };
    return BasePaletteItem;
}(draggable_element_1.DraggableElement));
exports.BasePaletteItem = BasePaletteItem;
var ElementPaletteItem = /** @class */ (function (_super) {
    __extends(ElementPaletteItem, _super);
    function ElementPaletteItem(typeRegistration, peerRegistration) {
        var _this = _super.call(this) || this;
        _this.typeRegistration = typeRegistration;
        _this.peerRegistration = peerRegistration;
        return _this;
    }
    ElementPaletteItem.prototype.getText = function () {
        return this.typeRegistration.typeName;
    };
    ElementPaletteItem.prototype.getIconClass = function () {
        return this.peerRegistration.iconClass;
    };
    ElementPaletteItem.prototype.createPeer = function (designer) {
        var peer = DesignerSurface.CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(designer, null, this.typeRegistration.createInstance());
        peer.initializeCardElement();
        return peer;
    };
    return ElementPaletteItem;
}(BasePaletteItem));
exports.ElementPaletteItem = ElementPaletteItem;
/* DO NOT REMOVE - future feature
class SnippetPaletteItem extends BasePaletteItem {
    protected getText(): string {
        return this.name;
    }

    protected getIconClass(): string {
        return null;
    }

    readonly name: string;
    snippet: object;

    constructor(name: string) {
        super();

        this.name = name;
    }

    createPeer(designer: Designer.CardDesigner): Designer.CardElementPeer {
        if (this.snippet) {
            let rootElementTypeName = this.snippet["type"];

            if (rootElementTypeName) {
                let adaptiveElement = Adaptive.AdaptiveCard.elementTypeRegistry.createInstance(rootElementTypeName);

                if (adaptiveElement) {
                    adaptiveElement.parse(this.snippet);

                    let peer = Designer.CardDesigner.cardElementPeerRegistry.createPeerInstance(designer, null, adaptiveElement);
                    peer.initializeCardElement();

                    return peer;
                }
            }
        }
    }
}
*/ 
//# sourceMappingURL=tool-palette.js.map