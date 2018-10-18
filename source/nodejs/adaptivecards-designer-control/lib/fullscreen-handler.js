"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var FullScreenHandler = /** @class */ (function () {
    function FullScreenHandler() {
        var _this = this;
        var untypedBody = document.body;
        if (typeof untypedBody.onfullscreenchange !== "undefined") {
            untypedBody.onfullscreenchange = function () { return _this.fullScrerenChanged(); };
        }
        else if (typeof untypedBody.onwebkitfullscreenchange !== "undefined") {
            untypedBody.onwebkitfullscreenchange = function () { return _this.fullScrerenChanged(); };
        }
        else if (typeof untypedBody.onwebkitfullscreenchange !== "undefined") {
            untypedBody.onmozfullscreenchange = function () { return _this.fullScrerenChanged(); };
        }
        else if (typeof untypedBody.onwebkitfullscreenchange !== "undefined") {
            untypedBody.MSFullscreenChange = function () { return _this.fullScrerenChanged(); };
        }
    }
    FullScreenHandler.prototype.fullScrerenChanged = function () {
        if (this.onFullScreenChanged) {
            this.onFullScreenChanged(this.isFullScreen);
        }
    };
    FullScreenHandler.prototype.enterFullScreen = function () {
        if (!this.isFullScreen) {
            var untypedBody = document.body;
            if (untypedBody.requestFullscreen) {
                untypedBody.requestFullscreen();
            }
            else if (untypedBody.webkitRequestFullscreen) {
                untypedBody.webkitRequestFullscreen();
            }
            else if (untypedBody.mozRequestFullScreen) {
                untypedBody.mozRequestFullScreen();
            }
            else if (untypedBody.msRequestFullscreen) {
                untypedBody.msRequestFullscreen();
            }
            else {
                alert("Your browser doesn't support fullscreen.");
            }
        }
    };
    FullScreenHandler.prototype.exitFullScreen = function () {
        if (this.isFullScreen) {
            var untypedDocument = document;
            if (untypedDocument.exitFullscreen) {
                untypedDocument.exitFullscreen();
            }
            else if (untypedDocument.webkitExitFullscreen) {
                untypedDocument.webkitExitFullscreen();
            }
            else if (untypedDocument.mozCancelFullScreen) {
                untypedDocument.mozCancelFullScreen();
            }
            else if (untypedDocument.msExitFullscreen) {
                untypedDocument.msExitFullscreen();
            }
        }
    };
    FullScreenHandler.prototype.toggleFullScreen = function () {
        if (this.isFullScreen) {
            this.exitFullScreen();
        }
        else {
            this.enterFullScreen();
        }
    };
    Object.defineProperty(FullScreenHandler.prototype, "isFullScreen", {
        get: function () {
            var untypedDocument = document;
            return untypedDocument.fullscreen || untypedDocument.webkitIsFullScreen || untypedDocument.mozFullScreen;
        },
        enumerable: true,
        configurable: true
    });
    return FullScreenHandler;
}());
exports.FullScreenHandler = FullScreenHandler;
//# sourceMappingURL=fullscreen-handler.js.map