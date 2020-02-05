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
var SkypeContainer = /** @class */ (function (_super) {
    __extends(SkypeContainer, _super);
    function SkypeContainer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    SkypeContainer.prototype.renderTo = function (hostElement) {
        this.cardHost.classList.add("skype-card");
        var frame = document.createElement("div");
        frame.className = "skype-frame";
        // Draw the hexagon bot logo
        var hexagonOuter = document.createElement("div");
        hexagonOuter.className = "skype-hexagon-outer";
        var hexagonInner = document.createElement("div");
        hexagonInner.className = "skype-hexagon-inner";
        var botLogo = document.createElement("div");
        botLogo.className = "skype-bot-logo";
        hexagonOuter.appendChild(hexagonInner);
        hexagonInner.appendChild(botLogo);
        frame.appendChild(hexagonOuter);
        frame.appendChild(this.cardHost);
        hostElement.appendChild(frame);
    };
    SkypeContainer.prototype.getHostConfig = function () {
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
                    backgroundColor: "#EAEAEA",
                    foregroundColors: {
                        default: {
                            default: "#333333",
                            subtle: "#EE333333"
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
                            default: "#54a254",
                            subtle: "#DD54a254"
                        },
                        warning: {
                            default: "#c3ab23",
                            subtle: "#DDc3ab23"
                        }
                    }
                },
                emphasis: {
                    backgroundColor: "#08000000",
                    foregroundColors: {
                        default: {
                            default: "#333333",
                            subtle: "#EE333333"
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
                            default: "#54a254",
                            subtle: "#DD54a254"
                        },
                        warning: {
                            default: "#c3ab23",
                            subtle: "#DDc3ab23"
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
                    actionMode: Adaptive.ShowCardActionMode.Popup,
                    inlineTopMargin: 16
                },
                actionsOrientation: Adaptive.Orientation.Vertical,
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
                spacing: 5
            }
        });
    };
    return SkypeContainer;
}(Designer.HostContainer));
exports.SkypeContainer = SkypeContainer;
//# sourceMappingURL=skype-container.js.map