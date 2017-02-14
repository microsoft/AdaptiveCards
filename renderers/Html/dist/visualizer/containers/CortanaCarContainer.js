"use strict";
var __extends = (this && this.__extends) || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
};
var HostContainer_1 = require("./HostContainer");
var Adaptive = require("../../Adaptive");
var Utils = require("../../Utils");
var CortanaCarContainer = (function (_super) {
    __extends(CortanaCarContainer, _super);
    function CortanaCarContainer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    CortanaCarContainer.prototype.render = function (card) {
        var element = document.createElement("div");
        Adaptive.ActionBar.buttonStyle = Adaptive.ActionButtonStyle.Link;
        var renderedCard = card.render();
        var imgDiv = document.createElement("div");
        imgDiv.classList.add("title");
        var img = document.createElement("img");
        img.classList.add("image", "cortanaLogo");
        img.src = "./../../assets/cortana-logo.png";
        Utils.appendChild(imgDiv, img);
        renderedCard.insertBefore(imgDiv, renderedCard.firstChild);
        Utils.appendChild(element, renderedCard);
        var hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, _super.prototype.render.call(this, card));
        return hostDiv;
    };
    return CortanaCarContainer;
}(HostContainer_1.HostContainer));
exports.CortanaCarContainer = CortanaCarContainer;
//# sourceMappingURL=CortanaCarContainer.js.map