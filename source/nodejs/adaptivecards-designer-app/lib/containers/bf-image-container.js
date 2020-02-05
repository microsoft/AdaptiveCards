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
var BotFrameworkContainer = /** @class */ (function (_super) {
    __extends(BotFrameworkContainer, _super);
    function BotFrameworkContainer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    BotFrameworkContainer.prototype.renderTo = function (hostElement) {
        this.cardHost.classList.add("bf-images-card");
        var frame = document.createElement("div");
        frame.className = "bf-images-frame";
        frame.appendChild(this.cardHost);
        hostElement.appendChild(frame);
    };
    BotFrameworkContainer.prototype.getHostConfig = function () {
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
            supportsInteractivity: false,
            fontFamily: "'Segoe UI', Calibri, Candara, Segoe, Optima, Arial, sans-serif;",
            fontSizes: {
                small: 12,
                default: 14,
                medium: 16,
                large: 19,
                extraLarge: 22
            },
            fontWeights: {
                lighter: 200,
                default: 400,
                bolder: 600
            },
            containerStyles: {
                default: {
                    backgroundColor: "#FFFFFF",
                    foregroundColors: {
                        default: {
                            default: "#FF101010",
                            subtle: "#b2101010"
                        },
                        accent: {
                            default: "#FF0000FF",
                            subtle: "#b20000FF"
                        },
                        good: {
                            default: "#FF008000",
                            subtle: "#b2008000"
                        },
                        warning: {
                            default: "#FFFFD700",
                            subtle: "#b2FFD700"
                        },
                        attention: {
                            default: "#FF8B0000",
                            subtle: "#b28B0000"
                        }
                    }
                },
                emphasis: {
                    backgroundColor: "#08000000",
                    foregroundColors: {
                        default: {
                            default: "#FF101010",
                            subtle: "#b2101010"
                        },
                        accent: {
                            default: "#FF0000FF",
                            subtle: "#b20000FF"
                        },
                        good: {
                            default: "#FF008000",
                            subtle: "#b2008000"
                        },
                        warning: {
                            default: "#FFFFD700",
                            subtle: "#b2FFD700"
                        },
                        attention: {
                            default: "#FF8B0000",
                            subtle: "#b28B0000"
                        }
                    }
                }
            },
            imageSizes: {
                small: 60,
                medium: 120,
                large: 180
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
                actionAlignment: Adaptive.ActionAlignment.Left
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
                    maxWidth: 150
                },
                value: {
                    color: Adaptive.TextColor.Default,
                    size: Adaptive.TextSize.Default,
                    isSubtle: false,
                    weight: Adaptive.TextWeight.Default,
                    wrap: true
                },
                spacing: 10
            }
        });
    };
    return BotFrameworkContainer;
}(Designer.HostContainer));
exports.BotFrameworkContainer = BotFrameworkContainer;
//# sourceMappingURL=bf-image-container.js.map