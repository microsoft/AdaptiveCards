"use strict";
var __extends = (this && this.__extends) || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
};
var HostContainer_1 = require("./HostContainer");
var Adaptive = require("../../Adaptive");
var Utils = require("../../Utils");
var ToastContainer = (function (_super) {
    __extends(ToastContainer, _super);
    function ToastContainer(width, styleSheet) {
        var _this = _super.call(this, styleSheet) || this;
        _this._width = width;
        return _this;
    }
    ToastContainer.prototype.render = function (card) {
        var element = document.createElement("div");
        element.style.border = "#474747 1px solid";
        element.style.width = this._width + "px";
        element.style.backgroundColor = ToastContainer.backgroundColor;
        element.style.overflow = "hidden";
        // TODO: Bring this back once the Toast schema is ready
        // if (card.title != undefined || card.description1 != undefined) {
        //     let headerElement = document.createElement("div");
        //     headerElement.className = "headerContainer";
        //     let html: string = '';
        //     html += '<div style="flex: 0 0 auto; margin-right: 10px;">';
        //     html += '  <img class="image autoSize" style="overflow: hidden; margin-top: 0px;" src="./assets/appicon.png"/>';
        //     html += '</div>';
        //     html += '<div style="flex: 1 1 100%">';
        //     if (card.title != undefined) {
        //         html += '  <div class="text defaultSize lightColor">' + card.title + '</div>';
        //     }
        //     if (card.description1 != undefined) {
        //         html += '  <div class="text defaultSize lightColor `sub`tle">' + card.description1 + '</div>';
        //     }
        //     if (card.description2 != undefined) {
        //         html += '  <div class="text small lightColor subtle">' + card.description2 + '</div>';
        //     }
        //     html += '</div>';
        //     headerElement.innerHTML = html;
        //     appendChild(element, headerElement);
        // }
        card.body.textColor = ToastContainer.textColor;
        Adaptive.ActionBar.buttonStyle = Adaptive.ActionButtonStyle.Push;
        var renderedCard = card.render();
        Utils.appendChild(element, renderedCard);
        var hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, _super.prototype.render.call(this, card));
        return hostDiv;
    };
    return ToastContainer;
}(HostContainer_1.HostContainer));
ToastContainer.backgroundColor = "#1F1F1F";
ToastContainer.textColor = Adaptive.TextColor.Light;
exports.ToastContainer = ToastContainer;
//# sourceMappingURL=ToastContainer.js.map