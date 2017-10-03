"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var Enums = require("./enums");
var Utils = require("./utils");
function parseSpacingDefinition(obj) {
    return obj ? {
        top: obj["top"],
        right: obj["right"],
        bottom: obj["bottom"],
        left: obj["left"]
    } : null;
}
function parsePaddingDefinition(obj) {
    return obj ? {
        top: Utils.parseHostConfigEnum(Enums.Padding, obj["top"], Enums.Padding.None),
        right: Utils.parseHostConfigEnum(Enums.Padding, obj["right"], Enums.Padding.None),
        bottom: Utils.parseHostConfigEnum(Enums.Padding, obj["bottom"], Enums.Padding.None),
        left: Utils.parseHostConfigEnum(Enums.Padding, obj["left"], Enums.Padding.None),
    } : null;
}
function parseTextColorDefinition(obj) {
    return obj ? {
        normal: obj["normal"],
        subtle: obj["subtle"]
    } : null;
}
function parseColorPaletteDefinition(obj) {
    return obj ? {
        backgroundColor: obj["backgroundColor"],
        fontColors: {
            default: parseTextColorDefinition(obj["fontColors"]["default"]),
            accent: parseTextColorDefinition(obj["fontColors"]["accent"]),
            good: parseTextColorDefinition(obj["fontColors"]["good"]),
            warning: parseTextColorDefinition(obj["fontColors"]["warning"]),
            attention: parseTextColorDefinition(obj["fontColors"]["attention"])
        }
    } : null;
}
function parseAdaptiveCardConfiguration(obj) {
    return obj ? {
        allowCustomStyle: obj["allowCustomStyle"]
    } : null;
}
function parseImageConfiguration(obj) {
    return obj ? {
        size: obj["size"]
    } : null;
}
function parseImageSetConfiguration(obj) {
    return obj ? {
        imageSize: obj["imageSize"],
        maxImageHeight: Utils.getValueOrDefault("maxImageHeight", 100)
    } : null;
}
function parseFactTextDefinition(obj) {
    return obj ? {
        size: Utils.parseHostConfigEnum(Enums.TextSize, obj["size"], Enums.TextSize.Default),
        color: Utils.parseHostConfigEnum(Enums.TextColor, obj["color"], Enums.TextColor.Default),
        isSubtle: obj["isSubtle"],
        weight: Utils.parseHostConfigEnum(Enums.TextWeight, obj["weight"], Enums.TextWeight.Default),
        wrap: obj["wrap"]
    } : null;
}
function parseFactTitleDefinition(obj) {
    var result = parseFactTextDefinition(obj);
    if (result) {
        result.maxWidth = obj["maxWidth"];
    }
    return result;
}
function parseFactSetConfiguration(obj) {
    return obj ? {
        title: parseFactTitleDefinition(obj["title"]),
        value: parseFactTextDefinition(obj["value"]),
        spacing: obj["spacing"]
    } : null;
}
function parseShowCardActionConfiguration(obj) {
    return obj ? {
        actionMode: Utils.parseHostConfigEnum(Enums.ShowCardActionMode, obj["actionMode"], Enums.ShowCardActionMode.Inline),
        inlineTopMargin: obj["inlineTopMargin"],
        style: Utils.parseHostConfigEnum(Enums.ContainerStyle, obj["style"], Enums.ContainerStyle.Emphasis)
    } : null;
}
function parseActionsConfiguration(obj) {
    return obj ? {
        maxActions: obj["maxActions"],
        spacing: Utils.parseHostConfigEnum(Enums.Spacing, obj["spacing"], Enums.Spacing.Default),
        buttonSpacing: obj["buttonSpacing"],
        showCard: parseShowCardActionConfiguration(obj["showCard"]),
        actionsOrientation: Utils.parseHostConfigEnum(Enums.Orientation, obj["actionsOrientation"], Enums.Orientation.Horizontal),
        actionAlignment: Utils.parseHostConfigEnum(Enums.ActionAlignment, obj["actionAlignment"], Enums.ActionAlignment.Left),
    } : null;
}
function parseHostConfig(serializedConfiguration) {
    var obj = JSON.parse(serializedConfiguration);
    return obj ? {
        supportsInteractivity: obj["supportsInteractivity"],
        fontFamily: obj["fontFamily"],
        fontSizes: {
            small: obj["fontSizes"]["small"],
            default: obj["fontSizes"]["default"],
            medium: obj["fontSizes"]["medium"],
            large: obj["fontSizes"]["large"],
            extraLarge: obj["fontSizes"]["extraLarge"]
        },
        fontWeights: {
            lighter: obj["fontWeights"]["lighter"],
            default: obj["fontWeights"]["default"],
            bolder: obj["fontWeights"]["bolder"]
        },
        imageSizes: {
            small: obj["imageSizes"]["small"],
            medium: obj["imageSizes"]["medium"],
            large: obj["imageSizes"]["large"],
        },
        containerStyles: {
            default: parseColorPaletteDefinition(obj["containerStyles"]["default"]),
            emphasis: parseColorPaletteDefinition(obj["containerStyles"]["emphasis"])
        },
        spacing: {
            small: obj["spacing"]["small"],
            default: obj["spacing"]["default"],
            medium: obj["spacing"]["medium"],
            large: obj["spacing"]["large"],
            extraLarge: obj["spacing"]["extraLarge"],
            padding: obj["spacing"]["padding"]
        },
        separator: {
            lineThickness: obj["separator"]["lineThickness"],
            lineColor: obj["separator"]["lineColor"]
        },
        actions: parseActionsConfiguration(obj["actions"]),
        adaptiveCard: parseAdaptiveCardConfiguration(obj["adaptiveCard"]),
        image: parseImageConfiguration(obj["image"]),
        imageSet: parseImageSetConfiguration(obj["imageSet"]),
        factSet: parseFactSetConfiguration(obj["factSet"])
    } : null;
}
exports.parseHostConfig = parseHostConfig;
//# sourceMappingURL=host-config.js.map