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
var CortanaCarContainer = (function (_super) {
    __extends(CortanaCarContainer, _super);
    function CortanaCarContainer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    CortanaCarContainer.prototype.applyOptions = function () {
        _super.prototype.applyOptions.call(this);
        Adaptive.AdaptiveCard.options.actionShowCardInPopup = true;
    };
    CortanaCarContainer.prototype.render = function (card) {
        var element = document.createElement("div");
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