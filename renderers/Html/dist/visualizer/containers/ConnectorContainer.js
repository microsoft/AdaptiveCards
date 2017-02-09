"use strict";
var __extends = (this && this.__extends) || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
};
var HostContainer_1 = require("./HostContainer");
var ConnectorContainer = (function (_super) {
    __extends(ConnectorContainer, _super);
    function ConnectorContainer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ConnectorContainer.prototype.renderHeader = function (card) {
        var headerElement = null;
        // if (card.title != undefined || card.description1 != undefined) {
        //     headerElement = document.createElement("div");
        //     headerElement.className = "headerContainer";
        //     let html = '<div>';
        //     let spaceNeeded = false;
        //     if (card.title != undefined) {
        //         html += '  <div class="text medium bolder defaultColor">' + card.title + '</div>';
        //         spaceNeeded = true;
        //     }
        //     if (card.description1 != undefined) {
        //         html += '  <div class="text defaultSize defaultColor"';
        //         if (spaceNeeded) {
        //             html += ' style="padding-top: 16px;"';
        //         }
        //         html += '>' + card.description1 + '</div>';
        //     }
        //     if (card.description2 != undefined) {
        //         html += '  <div class="text defaultSize defaultColor subtle">' + card.description2 + '</div>';
        //     }
        //     html += '</div>';
        //     headerElement.innerHTML = html;
        // }
        return headerElement;
    };
    return ConnectorContainer;
}(HostContainer_1.HostContainer));
exports.ConnectorContainer = ConnectorContainer;
//# sourceMappingURL=ConnectorContainer.js.map