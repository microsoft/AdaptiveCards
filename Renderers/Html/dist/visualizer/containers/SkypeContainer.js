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
var SkypeContainer = (function (_super) {
    __extends(SkypeContainer, _super);
    function SkypeContainer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    SkypeContainer.prototype.applyOptions = function () {
        _super.prototype.applyOptions.call(this);
        Adaptive.AdaptiveCard.options.actionShowCardInPopup = true;
        Adaptive.AdaptiveCard.options.defaultActionButtonStyle = Adaptive.ActionButtonStyle.Push;
    };
    SkypeContainer.prototype.render = function (card) {
        var element = document.createElement("div");
        element.className = "skypeContainer";
        // Draw the hexagon bot logo
        var botElement = document.createElement("div");
        botElement.className = "hexagon";
        var botElementIn1 = document.createElement("div");
        botElementIn1.className = "hexagon-in1";
        botElement.appendChild(botElementIn1);
        var botElementIn2 = document.createElement("div");
        botElementIn2.className = "hexagon-in2";
        botElementIn1.appendChild(botElementIn2);
        //card.onAction = (action) => { alert(action.title);}
        var renderedCard = card.render();
        Utils.appendChild(element, botElement);
        Utils.appendChild(element, renderedCard);
        var hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, _super.prototype.render.call(this, card));
        return hostDiv;
    };
    return SkypeContainer;
}(HostContainer_1.HostContainer));
exports.SkypeContainer = SkypeContainer;
//# sourceMappingURL=SkypeContainer.js.map