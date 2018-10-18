"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var PeerCommand = /** @class */ (function () {
    function PeerCommand(init) {
        this.isPromotable = false;
        Object.assign(this, init);
    }
    PeerCommand.prototype.internalRender = function () {
        var _this = this;
        var buttonElement = document.createElement("button");
        buttonElement.type = "button";
        buttonElement.title = this.name;
        buttonElement.classList.add("acd-peerButton");
        buttonElement.classList.add(this.iconClass);
        buttonElement.style.display = "flex";
        buttonElement.style.flex = "0 0 auto";
        buttonElement.style.alignItems = "center";
        buttonElement.onclick = function (e) {
            if (_this.execute) {
                _this.execute(_this, buttonElement);
            }
        };
        buttonElement.onpointerdown = function (e) { e.cancelBubble = true; };
        return buttonElement;
    };
    PeerCommand.prototype.render = function () {
        this._renderedElement = this.internalRender();
        return this._renderedElement;
    };
    Object.defineProperty(PeerCommand.prototype, "renderedElement", {
        get: function () {
            return this._renderedElement;
        },
        enumerable: true,
        configurable: true
    });
    return PeerCommand;
}());
exports.PeerCommand = PeerCommand;
//# sourceMappingURL=peer-command.js.map