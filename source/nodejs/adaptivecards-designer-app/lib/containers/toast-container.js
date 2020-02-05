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
var Adaptive = require("adaptivecards");
var Designer = require("adaptivecards-designer");
var ToastContainer = /** @class */ (function (_super) {
    __extends(ToastContainer, _super);
    function ToastContainer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ToastContainer.prototype.renderTo = function (hostElement) {
        this.cardHost.classList.add("toast-card");
        var frame = document.createElement("div");
        frame.className = "toast-frame";
        frame.appendChild(this.cardHost);
        hostElement.appendChild(frame);
    };
    ToastContainer.prototype.getHostConfig = function () {
        return new Adaptive.HostConfig({
            spacing: {
                small: 3,
                default: 8,
                medium: 20,
                large: 30,
                extraLarge: 40,
                padding: 10
            },
            separator: {
                lineThickness: 1,
                lineColor: "#EEEEEE"
            },
            supportsInteractivity: true,
            fontFamily: "Segoe UI",
            fontSizes: {
                small: 12,
                default: 14,
                medium: 17,
                large: 21,
                extraLarge: 26
            },
            fontWeights: {
                lighter: 200,
                default: 400,
                bolder: 600
            },
            containerStyles: {
                default: {
                    backgroundColor: "#1F1F1F",
                    foregroundColors: {
                        default: {
                            default: "#FFFFFF",
                            subtle: "#88FFFFFF"
                        },
                        accent: {
                            default: "#2E89FC",
                            subtle: "#882E89FC"
                        },
                        attention: {
                            default: "#FF0000",
                            subtle: "#DDFF0000"
                        },
                        good: {
                            default: "#00FF00",
                            subtle: "#DD00FF00"
                        },
                        warning: {
                            default: "#FFD800",
                            subtle: "#DDFFD800"
                        }
                    }
                },
                emphasis: {
                    backgroundColor: "#19FFFFFF",
                    foregroundColors: {
                        default: {
                            default: "#FFFFFF",
                            subtle: "#88FFFFFF"
                        },
                        accent: {
                            default: "#2E89FC",
                            subtle: "#882E89FC"
                        },
                        attention: {
                            default: "#FFD800",
                            subtle: "#DDFFD800"
                        },
                        good: {
                            default: "#00FF00",
                            subtle: "#DD00FF00"
                        },
                        warning: {
                            default: "#FF0000",
                            subtle: "#DDFF0000"
                        }
                    }
                }
            },
            imageSizes: {
                small: 40,
                medium: 80,
                large: 160
            },
            actions: {
                maxActions: 5,
                spacing: Adaptive.Spacing.Default,
                buttonSpacing: 10,
                showCard: {
                    actionMode: Adaptive.ShowCardActionMode.Inline,
                    inlineTopMargin: 16
                },
                actionsOrientation: Adaptive.Orientation.Horizontal,
                actionAlignment: Adaptive.ActionAlignment.Stretch
            },
            adaptiveCard: {
                allowCustomStyle: false
            },
            imageSet: {
                imageSize: Adaptive.Size.Medium,
                maxImageHeight: 100
            },
            factSet: {
                title: {
                    color: Adaptive.TextColor.Default,
                    size: Adaptive.TextSize.Default,
                    isSubtle: false,
                    weight: Adaptive.TextWeight.Bolder,
                    wrap: true,
                    maxWidth: 150,
                },
                value: {
                    color: Adaptive.TextColor.Default,
                    size: Adaptive.TextSize.Default,
                    isSubtle: false,
                    weight: Adaptive.TextWeight.Default,
                    wrap: true,
                },
                spacing: 10
            }
        });
    };
    return ToastContainer;
}(Designer.HostContainer));
exports.ToastContainer = ToastContainer;
//# sourceMappingURL=toast-container.js.map