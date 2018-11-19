"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
        return extendStatics(d, b);
    }
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var host_container_1 = require("./host-container");
var DefaultContainer = /** @class */ (function (_super) {
    __extends(DefaultContainer, _super);
    function DefaultContainer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    DefaultContainer.prototype.renderTo = function (hostElement) {
        hostElement.classList.add("card-frame");
        hostElement.appendChild(this.cardHost);
    };
    return DefaultContainer;
}(host_container_1.HostContainer));
exports.DefaultContainer = DefaultContainer;
//# sourceMappingURL=default-container.js.map