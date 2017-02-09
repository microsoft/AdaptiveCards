"use strict";
var __extends = (this && this.__extends) || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
};
var HostContainer_1 = require("./HostContainer");
var Adaptive = require("../../Adaptive");
var Utils = require("../../Utils");
var BingContainer = (function (_super) {
    __extends(BingContainer, _super);
    function BingContainer(width, height, styleSheet) {
        var _this = _super.call(this, styleSheet) || this;
        _this._width = width;
        _this._height = height;
        return _this;
    }
    BingContainer.prototype.render = function (card) {
        var element = document.createElement("div");
        element.style.width = this._width + "px";
        element.style.height = this._height + "px";
        element.style.backgroundColor = BingContainer.backgroundColor;
        element.style.overflow = "hidden";
        card.body.textColor = BingContainer.textColor;
        Adaptive.ActionBar.buttonStyle = Adaptive.ActionButtonStyle.Push;
        var renderedCard = card.render();
        renderedCard.style.height = "100%";
        Utils.appendChild(element, renderedCard);
        var hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, _super.prototype.render.call(this, card));
        return hostDiv;
    };
    return BingContainer;
}(HostContainer_1.HostContainer));
BingContainer.backgroundColor = "#fff";
BingContainer.textColor = Adaptive.TextColor.Dark;
exports.BingContainer = BingContainer;
//# sourceMappingURL=BingContainer.js.map