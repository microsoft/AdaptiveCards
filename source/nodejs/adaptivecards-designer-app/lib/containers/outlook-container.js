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
var ToggleVisibilityAction = /** @class */ (function (_super) {
    __extends(ToggleVisibilityAction, _super);
    function ToggleVisibilityAction() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.targetElementIds = [];
        return _this;
    }
    ToggleVisibilityAction.prototype.getJsonTypeName = function () {
        return "Action.ToggleVisibility";
    };
    ToggleVisibilityAction.prototype.execute = function () {
        if (this.targetElementIds) {
            for (var i = 0; i < this.targetElementIds.length; i++) {
                var targetElement = this.parent.getRootElement().getElementById(this.targetElementIds[i]);
                if (targetElement) {
                    targetElement.isVisible = !targetElement.isVisible;
                }
            }
        }
    };
    ToggleVisibilityAction.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.targetElementIds = json["targetElements"];
    };
    return ToggleVisibilityAction;
}(Adaptive.Action));
exports.ToggleVisibilityAction = ToggleVisibilityAction;
var OutlookContainer = /** @class */ (function (_super) {
    __extends(OutlookContainer, _super);
    function OutlookContainer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    OutlookContainer.prototype.renderTo = function (hostElement) {
        hostElement.classList.add("outlook-frame");
        hostElement.appendChild(this.cardHost);
    };
    OutlookContainer.prototype.initialize = function () {
        _super.prototype.initialize.call(this);
        Adaptive.AdaptiveCard.elementTypeRegistry.registerType("ActionSet", function () { return new Adaptive.ActionSet(); });
        Adaptive.AdaptiveCard.actionTypeRegistry.unregisterType("Action.Submit");
        Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Action.Http", function () { return new Adaptive.HttpAction(); });
        Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Action.ToggleVisibility", function () { return new ToggleVisibilityAction(); });
        Adaptive.AdaptiveCard.useMarkdownInRadioButtonAndCheckbox = false;
    };
    OutlookContainer.prototype.parsePadding = function (json) {
        if (json) {
            if (typeof json === "string") {
                var uniformPadding = Adaptive.getEnumValueOrDefault(Adaptive.Spacing, json, Adaptive.Spacing.None);
                return new Adaptive.PaddingDefinition(uniformPadding, uniformPadding, uniformPadding, uniformPadding);
            }
            else if (typeof json === "object") {
                return new Adaptive.PaddingDefinition(Adaptive.getEnumValueOrDefault(Adaptive.Spacing, json["top"], Adaptive.Spacing.None), Adaptive.getEnumValueOrDefault(Adaptive.Spacing, json["right"], Adaptive.Spacing.None), Adaptive.getEnumValueOrDefault(Adaptive.Spacing, json["bottom"], Adaptive.Spacing.None), Adaptive.getEnumValueOrDefault(Adaptive.Spacing, json["left"], Adaptive.Spacing.None));
            }
        }
        return null;
    };
    OutlookContainer.prototype.parseElement = function (element, json) {
        if (typeof json["isVisible"] === "boolean") {
            element.isVisible = json["isVisible"];
        }
        if (element instanceof Adaptive.AdaptiveCard) {
            var card = element;
            var actionArray = [];
            card["resources"] = { actions: actionArray };
            if (typeof json["resources"] === "object") {
                var actionResources = json["resources"]["actions"];
                for (var i = 0; i < actionResources.length; i++) {
                    var action = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(actionResources[i]["type"]);
                    if (action) {
                        action.parse(actionResources[i]);
                        action.setParent(card);
                        actionArray.push(action);
                    }
                }
            }
        }
        if (element instanceof Adaptive.Image) {
            element.backgroundColor = json["backgroundColor"];
        }
        if (element instanceof Adaptive.Container) {
            var padding = this.parsePadding(json["padding"]);
            if (padding) {
                element.padding = padding;
            }
        }
        if (element instanceof Adaptive.ColumnSet) {
            var padding = this.parsePadding(json["padding"]);
            if (padding) {
                element.padding = padding;
            }
        }
    };
    OutlookContainer.prototype.anchorClicked = function (element, anchor) {
        var regEx = /^action:([a-z0-9]+)$/ig;
        var rootCard = element.getRootElement();
        var matches = regEx.exec(anchor.href);
        if (matches) {
            var actionId = matches[1];
            if (rootCard) {
                var actionArray = rootCard["resources"]["actions"];
                for (var i = 0; i < actionArray.length; i++) {
                    if (actionArray[i].id == actionId) {
                        actionArray[i].execute();
                        return true;
                    }
                }
            }
        }
        return false;
    };
    OutlookContainer.prototype.getHostConfig = function () {
        return new Adaptive.HostConfig({
            preExpandSingleShowCardAction: true,
            supportsInteractivity: true,
            fontFamily: "Segoe UI",
            spacing: {
                small: 10,
                default: 20,
                medium: 30,
                large: 40,
                extraLarge: 50,
                padding: 20
            },
            separator: {
                lineThickness: 1,
                lineColor: "#EEEEEE"
            },
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
            imageSizes: {
                small: 40,
                medium: 80,
                large: 160
            },
            containerStyles: {
                default: {
                    backgroundColor: "#FFFFFF",
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
                            default: "#cc3300",
                            subtle: "#DDcc3300"
                        },
                        good: {
                            default: "#54a254",
                            subtle: "#DD54a254"
                        },
                        warning: {
                            default: "#e69500",
                            subtle: "#DDe69500"
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
                            default: "#cc3300",
                            subtle: "#DDcc3300"
                        },
                        good: {
                            default: "#54a254",
                            subtle: "#DD54a254"
                        },
                        warning: {
                            default: "#e69500",
                            subtle: "#DDe69500"
                        }
                    }
                }
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
                allowCustomStyle: true
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
    return OutlookContainer;
}(Designer.HostContainer));
exports.OutlookContainer = OutlookContainer;
//# sourceMappingURL=outlook-container.js.map