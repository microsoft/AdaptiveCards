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
var HostContainer_1 = require("./HostContainer");
var Adaptive = require("../../Adaptive");
var Utils = require("../../Utils");
var LiveTileContainer = (function (_super) {
    __extends(LiveTileContainer, _super);
    function LiveTileContainer(width, height, styleSheet) {
        var _this = _super.call(this, styleSheet) || this;
        _this._width = width;
        _this._height = height;
        _this.supportsActionBar = false;
        return _this;
    }
    LiveTileContainer.prototype.applyOptions = function () {
        _super.prototype.applyOptions.call(this);
        Adaptive.AdaptiveCard.options.actionShowCardInPopup = false;
    };
    LiveTileContainer.prototype.render = function (card) {
        var element = document.createElement("div");
        element.style.width = this._width + "px";
        element.style.height = this._height + "px";
        element.style.backgroundColor = LiveTileContainer.backgroundColor;
        element.style.overflow = "hidden";
        card.root.textColor = LiveTileContainer.textColor;
        var renderedCard = card.render();
        renderedCard.style.height = "100%";
        Utils.appendChild(element, renderedCard);
        var hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, _super.prototype.render.call(this, card));
        return hostDiv;
    };
    return LiveTileContainer;
}(HostContainer_1.HostContainer));
LiveTileContainer.backgroundColor = "#0078D7";
LiveTileContainer.textColor = Adaptive.TextColor.Light;
exports.LiveTileContainer = LiveTileContainer;
//# sourceMappingURL=LiveTileContainer.js.map