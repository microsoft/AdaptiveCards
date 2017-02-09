"use strict";
var __extends = (this && this.__extends) || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
};
var ConnectorContainer_1 = require("./ConnectorContainer");
var Adaptive = require("../../Adaptive");
var Utils = require("../../Utils");
var OutlookConnectorContainer = (function (_super) {
    __extends(OutlookConnectorContainer, _super);
    function OutlookConnectorContainer(themeColor, styleSheet) {
        var _this = _super.call(this, styleSheet) || this;
        _this._themeColor = themeColor;
        return _this;
    }
    OutlookConnectorContainer.prototype.render = function (card) {
        var element = document.createElement("div");
        element.style.borderTop = "1px solid #F1F1F1";
        element.style.borderRight = "1px solid #F1F1F1";
        element.style.borderBottom = "1px solid #F1F1F1";
        if (Utils.isNullOrEmpty(this._themeColor)) {
            element.style.border = "1px solid #F1F1F1";
        }
        else {
            element.style.borderLeft = "3px solid " + this._themeColor;
        }
        var headerElement = this.renderHeader(card);
        if (headerElement != null) {
            Utils.appendChild(element, headerElement);
        }
        Adaptive.ActionBar.buttonStyle = Adaptive.ActionButtonStyle.Link;
        var renderedCard = card.render();
        Utils.appendChild(element, renderedCard);
        var hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, _super.prototype.render.call(this, card));
        return hostDiv;
    };
    return OutlookConnectorContainer;
}(ConnectorContainer_1.ConnectorContainer));
exports.OutlookConnectorContainer = OutlookConnectorContainer;
//# sourceMappingURL=OutlookConnectorContainer.js.map