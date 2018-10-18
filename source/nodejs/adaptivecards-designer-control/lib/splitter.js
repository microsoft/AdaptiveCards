"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var Splitter = /** @class */ (function () {
    function Splitter(attachedTo, sizedElement, isVertical) {
        if (isVertical === void 0) { isVertical = false; }
        var _this = this;
        this._isVertical = false;
        this.minimum = 50;
        this.attachedTo = attachedTo;
        this._sizedELement = sizedElement;
        this._isVertical = isVertical;
        this.attachedTo.onmousedown = function (e) { e.preventDefault(); };
        this.attachedTo.onpointerdown = function (e) { _this.pointerDown(e); };
        this.attachedTo.onpointermove = function (e) { _this.pointerMove(e); };
        this.attachedTo.onpointerup = function (e) { _this.pointerUp(e); };
    }
    Splitter.prototype.pointerDown = function (e) {
        e.preventDefault();
        this.attachedTo.setPointerCapture(e.pointerId);
        this._lastClickedOffset = { x: e.x, y: e.y };
        this._isPointerDown = true;
    };
    Splitter.prototype.pointerMove = function (e) {
        if (this._isPointerDown) {
            e.preventDefault();
            var sizeApplied = false;
            var newSize = void 0;
            if (this._isVertical) {
                newSize = this._sizedELement.getBoundingClientRect().width - (e.x - this._lastClickedOffset.x);
                if (newSize >= this.minimum) {
                    this._sizedELement.style.width = newSize + "px";
                    sizeApplied = true;
                }
            }
            else {
                newSize = this._sizedELement.getBoundingClientRect().height - (e.y - this._lastClickedOffset.y);
                if (newSize >= this.minimum) {
                    this._sizedELement.style.height = newSize + "px";
                    sizeApplied = true;
                }
            }
            if (sizeApplied) {
                if (this.onResized) {
                    this.onResized(this, newSize);
                }
                this._lastClickedOffset = { x: e.x, y: e.y };
            }
        }
    };
    Splitter.prototype.pointerUp = function (e) {
        e.preventDefault();
        this.attachedTo.releasePointerCapture(e.pointerId);
        this._isPointerDown = false;
    };
    return Splitter;
}());
exports.Splitter = Splitter;
//# sourceMappingURL=splitter.js.map