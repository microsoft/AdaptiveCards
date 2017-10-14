"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var Enums = require("./enums");
var Utils = require("./utils");
var SpacingDefinition = /** @class */ (function () {
    function SpacingDefinition(obj) {
        this.left = 0;
        this.top = 0;
        this.right = 0;
        this.bottom = 0;
        if (obj) {
            this.top = obj["top"] || this.top;
            this.right = obj["right"] || this.right;
            this.bottom = obj["bottom"] || this.bottom;
            this.left = obj["left"] || this.left;
        }
    }
    return SpacingDefinition;
}());
exports.SpacingDefinition = SpacingDefinition;
var PaddingDefinition = /** @class */ (function () {
    function PaddingDefinition(obj) {
        this.top = Enums.Padding.None;
        this.right = Enums.Padding.None;
        this.bottom = Enums.Padding.None;
        this.left = Enums.Padding.None;
        if (obj) {
            this.top = Utils.parseHostConfigEnum(Enums.Padding, obj["top"], Enums.Padding.None);
            this.right = Utils.parseHostConfigEnum(Enums.Padding, obj["right"], Enums.Padding.None);
            this.bottom = Utils.parseHostConfigEnum(Enums.Padding, obj["bottom"], Enums.Padding.None);
            this.left = Utils.parseHostConfigEnum(Enums.Padding, obj["left"], Enums.Padding.None);
        }
    }
    PaddingDefinition.prototype.toJSON = function () {
        return {
            top: Enums.Padding[this.top],
            right: Enums.Padding[this.right],
            bottom: Enums.Padding[this.bottom],
            left: Enums.Padding[this.left],
        };
    };
    return PaddingDefinition;
}());
exports.PaddingDefinition = PaddingDefinition;
var TextColorDefinition = /** @class */ (function () {
    function TextColorDefinition(obj) {
        this.normal = "#0000FF";
        this.subtle = "#222222";
        if (obj) {
            this.normal = obj["normal"] || this.normal;
            this.subtle = obj["subtle"] || this.subtle;
        }
    }
    return TextColorDefinition;
}());
exports.TextColorDefinition = TextColorDefinition;
var ContainerStyleDefinition = /** @class */ (function () {
    function ContainerStyleDefinition(obj) {
        this.fontColors = {
            default: new TextColorDefinition(),
            accent: new TextColorDefinition(),
            good: new TextColorDefinition(),
            warning: new TextColorDefinition(),
            attention: new TextColorDefinition()
        };
        if (obj) {
            this.backgroundColor = obj["backgroundColor"];
            this.fontColors = {
                default: new TextColorDefinition(obj["fontColors"]["default"]),
                accent: new TextColorDefinition(obj["fontColors"]["accent"]),
                good: new TextColorDefinition(obj["fontColors"]["good"]),
                warning: new TextColorDefinition(obj["fontColors"]["warning"]),
                attention: new TextColorDefinition(obj["fontColors"]["attention"])
            };
        }
    }
    return ContainerStyleDefinition;
}());
exports.ContainerStyleDefinition = ContainerStyleDefinition;
var AdaptiveCardConfig = /** @class */ (function () {
    function AdaptiveCardConfig(obj) {
        this.allowCustomStyle = false;
        if (obj) {
            this.allowCustomStyle = obj["allowCustomStyle"] || this.allowCustomStyle;
        }
    }
    return AdaptiveCardConfig;
}());
exports.AdaptiveCardConfig = AdaptiveCardConfig;
var ImageConfig = /** @class */ (function () {
    function ImageConfig(obj) {
        this.size = Enums.Size.Medium;
        if (obj) {
            this.size = obj["size"] || this.size;
        }
    }
    ImageConfig.prototype.toJSON = function () {
        return {
            size: Enums.Size[this.size]
        };
    };
    return ImageConfig;
}());
exports.ImageConfig = ImageConfig;
var ImageSetConfig = /** @class */ (function () {
    function ImageSetConfig(obj) {
        this.imageSize = Enums.Size.Medium;
        this.maxImageHeight = 100;
        if (obj) {
            this.imageSize = obj["imageSize"] || this.imageSize;
            this.maxImageHeight = Utils.getValueOrDefault("maxImageHeight", 100);
        }
    }
    ImageSetConfig.prototype.toJSON = function () {
        return {
            imageSize: Enums.Size[this.imageSize],
            maxImageHeight: this.maxImageHeight
        };
    };
    return ImageSetConfig;
}());
exports.ImageSetConfig = ImageSetConfig;
var FactTextDefinition = /** @class */ (function () {
    function FactTextDefinition(obj) {
        this.size = Enums.TextSize.Default;
        this.color = Enums.TextColor.Default;
        this.isSubtle = false;
        this.weight = Enums.TextWeight.Default;
        this.wrap = true;
        if (obj) {
            this.size = Utils.parseHostConfigEnum(Enums.TextSize, obj["size"], Enums.TextSize.Default);
            this.color = Utils.parseHostConfigEnum(Enums.TextColor, obj["color"], Enums.TextColor.Default);
            this.isSubtle = obj["isSubtle"] || this.isSubtle;
            this.weight = Utils.parseHostConfigEnum(Enums.TextWeight, obj["weight"], Enums.TextWeight.Default);
            this.wrap = obj["wrap"] || this.wrap;
        }
    }
    ;
    FactTextDefinition.prototype.toJSON = function () {
        return {
            size: Enums.TextSize[this.size],
            color: Enums.TextColor[this.color],
            isSubtle: this.isSubtle,
            weight: Enums.TextWeight[this.weight],
            warp: this.wrap
        };
    };
    return FactTextDefinition;
}());
exports.FactTextDefinition = FactTextDefinition;
var FactTitleDefinition = /** @class */ (function (_super) {
    __extends(FactTitleDefinition, _super);
    function FactTitleDefinition(obj) {
        var _this = _super.call(this, obj) || this;
        _this.maxWidth = 150;
        _this.weight = Enums.TextWeight.Bolder;
        if (obj) {
            _this.maxWidth = obj["maxWidth"] || _this.maxWidth;
        }
        return _this;
    }
    return FactTitleDefinition;
}(FactTextDefinition));
exports.FactTitleDefinition = FactTitleDefinition;
var FactSetConfig = /** @class */ (function () {
    function FactSetConfig(obj) {
        this.title = new FactTitleDefinition();
        this.value = new FactTextDefinition();
        this.spacing = 10;
        if (obj) {
            this.title = new FactTitleDefinition(obj["title"]);
            this.value = new FactTextDefinition(obj["value"]);
            this.spacing = obj["spacing"] || this.spacing;
        }
    }
    return FactSetConfig;
}());
exports.FactSetConfig = FactSetConfig;
var ShowCardActionConfig = /** @class */ (function () {
    function ShowCardActionConfig(obj) {
        this.actionMode = Enums.ShowCardActionMode.Inline;
        this.inlineTopMargin = 16;
        this.style = Enums.ContainerStyle.Emphasis;
        if (obj) {
            this.actionMode = Utils.parseHostConfigEnum(Enums.ShowCardActionMode, obj["actionMode"], Enums.ShowCardActionMode.Inline);
            this.inlineTopMargin = obj["inlineTopMargin"] || this.inlineTopMargin;
            this.style = Utils.parseHostConfigEnum(Enums.ContainerStyle, obj["style"], Enums.ContainerStyle.Emphasis);
        }
    }
    ShowCardActionConfig.prototype.toJSON = function () {
        return {
            actionMode: Enums.ShowCardActionMode[this.actionMode],
            inlineTopMargin: this.inlineTopMargin,
            style: Enums.ContainerStyle[this.style]
        };
    };
    return ShowCardActionConfig;
}());
exports.ShowCardActionConfig = ShowCardActionConfig;
var ActionsConfig = /** @class */ (function () {
    function ActionsConfig(obj) {
        this.maxActions = 5;
        this.spacing = Enums.Spacing.Default;
        this.buttonSpacing = 20;
        this.showCard = new ShowCardActionConfig();
        this.preExpandSingleShowCardAction = false;
        this.actionsOrientation = Enums.Orientation.Horizontal;
        this.actionAlignment = Enums.ActionAlignment.Left;
        if (obj) {
            this.maxActions = obj["maxActions"] || this.maxActions;
            this.spacing = Utils.parseHostConfigEnum(Enums.Spacing, obj["spacing"], Enums.Spacing.Default);
            this.buttonSpacing = obj["buttonSpacing"] || this.buttonSpacing;
            this.showCard = new ShowCardActionConfig(obj["showCard"]);
            this.preExpandSingleShowCardAction = Utils.getValueOrDefault(obj["preExpandSingleShowCardAction"], false);
            this.actionsOrientation = Utils.parseHostConfigEnum(Enums.Orientation, obj["actionsOrientation"], Enums.Orientation.Horizontal);
            this.actionAlignment = Utils.parseHostConfigEnum(Enums.ActionAlignment, obj["actionAlignment"], Enums.ActionAlignment.Left);
        }
    }
    ActionsConfig.prototype.toJSON = function () {
        return {
            maxActions: this.maxActions,
            spacing: Enums.Spacing[this.spacing],
            buttonSpacing: this.buttonSpacing,
            showCard: this.showCard,
            preExpandSingleShowCardAction: this.preExpandSingleShowCardAction,
            actionsOrientation: Enums.Orientation[this.actionsOrientation],
            actionAlignment: Enums.ActionAlignment[this.actionAlignment]
        };
    };
    return ActionsConfig;
}());
exports.ActionsConfig = ActionsConfig;
var ContainerStyleSet = /** @class */ (function () {
    function ContainerStyleSet(obj) {
        this.default = new ContainerStyleDefinition();
        this.emphasis = new ContainerStyleDefinition();
        this.emphasis.backgroundColor = "#EEEEEE";
        if (obj) {
            this.default = new ContainerStyleDefinition(obj["default"]);
            this.emphasis = new ContainerStyleDefinition(obj["emphasis"]);
        }
    }
    return ContainerStyleSet;
}());
exports.ContainerStyleSet = ContainerStyleSet;
var HostConfig = /** @class */ (function () {
    function HostConfig(obj) {
        this.supportsInteractivity = true;
        this.fontFamily = "Segoe UI";
        this.fontSizes = {
            small: 8,
            default: 10,
            medium: 12,
            large: 14,
            extraLarge: 16
        };
        this.fontWeights = {
            lighter: 200,
            default: 400,
            bolder: 600
        };
        this.imageSizes = {
            small: 40,
            medium: 80,
            large: 160
        };
        this.containerStyles = new ContainerStyleSet();
        this.spacing = {
            small: 3,
            default: 8,
            medium: 20,
            large: 30,
            extraLarge: 40,
            padding: 20
        };
        this.separator = {
            lineThickness: 1,
            lineColor: "#EEEEEE"
        };
        this.actions = new ActionsConfig();
        this.adaptiveCard = new AdaptiveCardConfig();
        this.image = new ImageConfig();
        this.imageSet = new ImageSetConfig();
        this.factSet = new FactSetConfig();
        if (obj) {
            if (typeof obj === "string" || obj instanceof String) {
                obj = JSON.parse(obj);
            }
            this.supportsInteractivity = obj["supportsInteractivity"] || this.supportsInteractivity;
            this.fontFamily = obj["fontFamily"] || this.fontFamily;
            this.fontSizes = {
                small: obj["fontSizes"]["small"] || this.fontSizes.small,
                default: obj["fontSizes"]["default"] || this.fontSizes.default,
                medium: obj["fontSizes"]["medium"] || this.fontSizes.medium,
                large: obj["fontSizes"]["large"] || this.fontSizes.large,
                extraLarge: obj["fontSizes"]["extraLarge"] || this.fontSizes.extraLarge
            };
            this.fontWeights = {
                lighter: obj["fontWeights"]["lighter"] || this.fontWeights.lighter,
                default: obj["fontWeights"]["default"] || this.fontWeights.default,
                bolder: obj["fontWeights"]["bolder"] || this.fontWeights.bolder
            };
            this.imageSizes = {
                small: obj["imageSizes"]["small"] || this.imageSizes.small,
                medium: obj["imageSizes"]["medium"] || this.imageSizes.medium,
                large: obj["imageSizes"]["large"] || this.imageSizes.large,
            };
            this.containerStyles = new ContainerStyleSet(obj["containerStyles"]);
            this.spacing = {
                small: obj["spacing"]["small"] || this.spacing.small,
                default: obj["spacing"]["default"] || this.spacing.default,
                medium: obj["spacing"]["medium"] || this.spacing.medium,
                large: obj["spacing"]["large"] || this.spacing.large,
                extraLarge: obj["spacing"]["extraLarge"] || this.spacing.extraLarge,
                padding: obj["spacing"]["padding"] || this.spacing.padding
            };
            this.separator = {
                lineThickness: obj["separator"]["lineThickness"] || this.separator.lineThickness,
                lineColor: obj["separator"]["lineColor"] || this.separator.lineColor
            };
            this.actions = new ActionsConfig(obj["actions"]);
            this.adaptiveCard = new AdaptiveCardConfig(obj["adaptiveCard"]);
            this.image = new ImageConfig(obj["image"]);
            this.imageSet = new ImageSetConfig(obj["imageSet"]);
            this.factSet = new FactSetConfig(obj["factSet"]);
        }
    }
    HostConfig.prototype.getEffectiveSpacing = function (spacing) {
        switch (spacing) {
            case Enums.Spacing.Small:
                return this.spacing.small;
            case Enums.Spacing.Default:
                return this.spacing.default;
            case Enums.Spacing.Medium:
                return this.spacing.medium;
            case Enums.Spacing.Large:
                return this.spacing.large;
            case Enums.Spacing.ExtraLarge:
                return this.spacing.extraLarge;
            case Enums.Spacing.Padding:
                return this.spacing.padding;
            default:
                return 0;
        }
    };
    HostConfig.prototype.getEffectivePadding = function (padding) {
        switch (padding) {
            case Enums.Padding.Default:
                return this.spacing.padding;
            default:
                return 0;
        }
    };
    HostConfig.prototype.paddingToSpacingDefinition = function (padding) {
        return new SpacingDefinition({
            top: this.getEffectivePadding(padding.top),
            right: this.getEffectivePadding(padding.right),
            bottom: this.getEffectivePadding(padding.bottom),
            left: this.getEffectivePadding(padding.left)
        });
    };
    HostConfig.prototype.getContainerStyleDefinition = function (containerStyle) {
        switch (containerStyle) {
            case Enums.ContainerStyle.Emphasis:
                return this.containerStyles.emphasis;
            default:
                return this.containerStyles.default;
        }
    };
    return HostConfig;
}());
exports.HostConfig = HostConfig;
//# sourceMappingURL=host-config.js.map