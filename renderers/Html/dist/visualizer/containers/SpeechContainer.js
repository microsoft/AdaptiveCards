"use strict";
var __extends = (this && this.__extends) || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
};
var HostContainer_1 = require("./HostContainer");
var Utils = require("../../Utils");
var SpeechContainer = (function (_super) {
    __extends(SpeechContainer, _super);
    function SpeechContainer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    SpeechContainer.prototype.render = function (card) {
        var hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, _super.prototype.render.call(this, card, true));
        return hostDiv;
    };
    return SpeechContainer;
}(HostContainer_1.HostContainer));
exports.SpeechContainer = SpeechContainer;
//# sourceMappingURL=SpeechContainer.js.map