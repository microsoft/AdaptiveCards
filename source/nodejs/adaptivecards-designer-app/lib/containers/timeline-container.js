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
var TimelineContainer = /** @class */ (function (_super) {
    __extends(TimelineContainer, _super);
    function TimelineContainer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    TimelineContainer.prototype.initialize = function () {
        Adaptive.AdaptiveCard.elementTypeRegistry.reset();
        Adaptive.AdaptiveCard.actionTypeRegistry.reset();
        Adaptive.AdaptiveCard.useAutomaticContainerBleeding = false;
        Adaptive.AdaptiveCard.useMarkdownInRadioButtonAndCheckbox = true;
        Adaptive.AdaptiveCard.useAdvancedCardBottomTruncation = false;
        Adaptive.AdaptiveCard.useAdvancedTextBlockTruncation = true;
    };
    TimelineContainer.prototype.renderTo = function (hostElement) {
        var target = document.getElementById("designerHost");
        var frame = document.createElement("div");
        frame.className = "timeline-frame";
        target.appendChild(frame);
        var cardContainer = document.createElement("div");
        cardContainer.className = "timeline-card";
        frame.appendChild(cardContainer);
        this.cardHost.style.height = "100%";
        this.cardHost.style.width = "100%";
        this.cardHost.style.overflow = "hidden";
        cardContainer.appendChild(this.cardHost);
        hostElement.appendChild(frame);
    };
    TimelineContainer.prototype.getHostConfig = function () {
        return new Adaptive.HostConfig({
            spacing: {
                small: 4,
                default: 12,
                medium: 20,
                large: 30,
                extraLarge: 40,
                padding: 15
            },
            separator: {
                lineThickness: 1,
                lineColor: "#EEEEEE"
            },
            supportsInteractivity: false,
            fontFamily: "Segoe UI",
            fontSizes: {
                small: 12,
                default: 14,
                medium: 20,
                large: 20,
                extraLarge: 26
            },
            fontWeights: {
                lighter: 200,
                default: 400,
                bolder: 700
            },
            containerStyles: {
                default: {
                    backgroundColor: "#535454",
                    foregroundColors: {
                        default: {
                            "default": "#FFFFFF",
                            "subtle": "#9C9E9F"
                        },
                        accent: {
                            "default": "#2E89FC",
                            "subtle": "#882E89FC"
                        },
                        attention: {
                            "default": "#FF0000",
                            "subtle": "#DDFF0000"
                        },
                        good: {
                            "default": "#00FF00",
                            "subtle": "#DD00FF00"
                        },
                        warning: {
                            "default": "#FFD800",
                            "subtle": "#DDFFD800"
                        }
                    }
                },
                emphasis: {
                    backgroundColor: "#33000000",
                    foregroundColors: {
                        default: {
                            "default": "#FFFFFF",
                            "subtle": "#9C9E9F"
                        },
                        accent: {
                            "default": "#2E89FC",
                            "subtle": "#882E89FC"
                        },
                        attention: {
                            "default": "#FF0000",
                            "subtle": "#DDFF0000"
                        },
                        good: {
                            "default": "#00FF00",
                            "subtle": "#DD00FF00"
                        },
                        warning: {
                            "default": "#FFD800",
                            "subtle": "#DDFFD800"
                        }
                    }
                }
            },
            imageSizes: {
                small: 40,
                medium: 80,
                large: 120
            },
            actions: {
                maxActions: 5,
                spacing: Adaptive.Spacing.Default,
                buttonSpacing: 20,
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
                    wrap: false,
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
    return TimelineContainer;
}(Designer.HostContainer));
exports.TimelineContainer = TimelineContainer;
//# sourceMappingURL=timeline-container.js.map