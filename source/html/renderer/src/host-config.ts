import * as Enums from "./enums";
import * as Utils from "./utils";

export class ISpacingDefinition {
    left: number;
    top: number;
    right: number;
    bottom: number
}

function parseSpacingDefinition(obj: any): ISpacingDefinition {
    return obj ? {
        top: obj["top"],
        right: obj["right"],
        bottom: obj["bottom"],
        left: obj["left"]
    } : null;
}

export class PaddingDefinition {
    top: Enums.Padding;
    right: Enums.Padding;
    bottom: Enums.Padding;
    left: Enums.Padding;

    toJSON() {
        return {
            top: Enums.Padding[this.top],
            right: Enums.Padding[this.right],
            bottom: Enums.Padding[this.bottom],
            left: Enums.Padding[this.left],
        }
    }
}

function parsePaddingDefinition(obj: any): PaddingDefinition {
    return obj ? Object.assign(new PaddingDefinition(), {
        top: Utils.parseHostConfigEnum(Enums.Padding, obj["top"], Enums.Padding.None),
        right: Utils.parseHostConfigEnum(Enums.Padding, obj["right"], Enums.Padding.None),
        bottom: Utils.parseHostConfigEnum(Enums.Padding, obj["bottom"], Enums.Padding.None),
        left: Utils.parseHostConfigEnum(Enums.Padding, obj["left"], Enums.Padding.None),
    }
    ) : null;
}

export class TextColorDefinition {
    normal: string;
    subtle: string;
}

function parseTextColorDefinition(obj: any): TextColorDefinition {
    return obj ? {
        normal: obj["normal"],
        subtle: obj["subtle"]
    } : null;
}

export class ContainerStyleDefinition {
    backgroundColor?: string;
    fontColors: {
        default: TextColorDefinition,
        accent: TextColorDefinition,
        good: TextColorDefinition,
        warning: TextColorDefinition,
        attention: TextColorDefinition
    };
}

function parseColorPaletteDefinition(obj: any): ContainerStyleDefinition {
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

export class AdaptiveCardConfig {
    allowCustomStyle: boolean;
}

function parseAdaptiveCardConfiguration(obj: any): AdaptiveCardConfig {
    return obj ? {
        allowCustomStyle: obj["allowCustomStyle"]
    } : null;
}

export class ImageConfig {
    size: Enums.Size;

    toJSON() {
        return {
            size: Enums.Size[this.size]
        }
    }
}

function parseImageConfiguration(obj: any): ImageConfig {
    return obj ? Object.assign(new ImageConfig(), {
        size: obj["size"]
    }) : null;
}

export class ImageSetConfig {
    imageSize: Enums.Size
    maxImageHeight: number

    toJSON() {
        return {
            imageSize: Enums.Size[this.imageSize],
            maxImageHeight: this.maxImageHeight
        }
    }
}

function parseImageSetConfiguration(obj: any): ImageSetConfig {
    return obj ? Object.assign(new ImageSetConfig(), {
        imageSize: obj["imageSize"],
        maxImageHeight: Utils.getValueOrDefault<number>("maxImageHeight", 100)
    }) : null;
}

export class FactTextDefinition {
    size: Enums.TextSize;
    color: Enums.TextColor;
    isSubtle: boolean;
    weight: Enums.TextWeight;
    wrap: boolean;

    toJSON(): any {
        return {
            size: Enums.TextSize[this.size],
            color: Enums.TextColor[this.color],
            isSubtle: this.isSubtle,
            weight: Enums.TextWeight[this.weight],
            warp: this.wrap
        }
    }
}

function parseFactTextDefinition(obj: any): FactTextDefinition {
    return obj ? Object.assign(new FactTextDefinition(), {
        size: Utils.parseHostConfigEnum(Enums.TextSize, obj["size"], Enums.TextSize.Default),
        color: Utils.parseHostConfigEnum(Enums.TextColor, obj["color"], Enums.TextColor.Default),
        isSubtle: obj["isSubtle"],
        weight: Utils.parseHostConfigEnum(Enums.TextWeight, obj["weight"], Enums.TextWeight.Default),
        wrap: obj["wrap"]
    }) : null;
}

export class FactTitleDefinition extends FactTextDefinition {
    maxWidth?: number;
}

function parseFactTitleDefinition(obj: any): FactTitleDefinition {
    var result: FactTitleDefinition = parseFactTextDefinition(obj);

    if (result) {
        result.maxWidth = obj["maxWidth"];
    }

    return result;
}

export class FactSetConfig {
    title: FactTitleDefinition = new FactTitleDefinition();
    value: FactTextDefinition = new FactTextDefinition();
    spacing: number;
}

function parseFactSetConfiguration(obj: any): FactSetConfig {
    return obj ? {
        title: parseFactTitleDefinition(obj["title"]),
        value: parseFactTextDefinition(obj["value"]),
        spacing: obj["spacing"]
    } : null;
}

export class ShowCardActionConfig {
    actionMode: Enums.ShowCardActionMode;
    inlineTopMargin: number;
    style?: Enums.ContainerStyle;

    toJSON() {
        return {
            actionMode: Enums.ShowCardActionMode[this.actionMode],
            inlineTopMargin: this.inlineTopMargin,
            style: Enums.ContainerStyle[this.style]
        }
    }
}

function parseShowCardActionConfiguration(obj: any): ShowCardActionConfig {
    return obj ? Object.assign(new ShowCardActionConfig(), {
        actionMode: Utils.parseHostConfigEnum(Enums.ShowCardActionMode, obj["actionMode"], Enums.ShowCardActionMode.Inline),
        inlineTopMargin: obj["inlineTopMargin"],
        style: Utils.parseHostConfigEnum(Enums.ContainerStyle, obj["style"], Enums.ContainerStyle.Emphasis)
    }) : null;
}

export class ActionsConfig {
    maxActions: number;
    spacing: Enums.Spacing;
    buttonSpacing: number;
    showCard: ShowCardActionConfig = new ShowCardActionConfig();
    preExpandSingleShowCardAction?: boolean;
    actionsOrientation: Enums.Orientation;
    actionAlignment: Enums.ActionAlignment;

    toJSON() {
        return {
            maxActions: this.maxActions,
            spacing: Enums.Spacing[this.spacing],
            buttonSpacing: this.buttonSpacing,
            showCard: this.showCard,
            preExpandSingleShowCardAction: this.preExpandSingleShowCardAction,
            actionsOrientation: Enums.Orientation[this.actionsOrientation],
            actionAlignment: Enums.ActionAlignment[this.actionAlignment]
        }
    }
}

function parseActionsConfiguration(obj: any): ActionsConfig {
    return obj ? Object.assign(new ActionsConfig(), {
        maxActions: obj["maxActions"],
        spacing: Utils.parseHostConfigEnum(Enums.Spacing, obj["spacing"], Enums.Spacing.Default),
        buttonSpacing: obj["buttonSpacing"],
        showCard: parseShowCardActionConfiguration(obj["showCard"]),
        preExpandSingleShowCardAction: Utils.getValueOrDefault<boolean>(obj["preExpandSingleShowCardAction"], false),
        actionsOrientation: Utils.parseHostConfigEnum(Enums.Orientation, obj["actionsOrientation"], Enums.Orientation.Horizontal),
        actionAlignment: Utils.parseHostConfigEnum(Enums.ActionAlignment, obj["actionAlignment"], Enums.ActionAlignment.Left),
    }) : null;
}

export class HostConfig {
    supportsInteractivity: boolean;
    fontFamily?: string;
    fontSizes: {
        small: number,
        default: number,
        medium: number,
        large: number,
        extraLarge: number
    };
    fontWeights: {
        lighter: number,
        default: number,
        bolder: number
    };
    imageSizes: {
        small: number,
        medium: number,
        large: number
    };
    containerStyles: {
        default: ContainerStyleDefinition,
        emphasis: ContainerStyleDefinition
    };
    spacing: {
        small: number,
        default: number,
        medium: number,
        large: number,
        extraLarge: number,
        padding: number
    };
    separator: {
        lineThickness: number,
        lineColor: string
    }
    actions: ActionsConfig = new ActionsConfig();
    adaptiveCard: AdaptiveCardConfig = new AdaptiveCardConfig();
    image: ImageConfig = new ImageConfig();
    imageSet: ImageSetConfig = new ImageSetConfig();
    factSet: FactSetConfig = new FactSetConfig();
}

export function parseHostConfig(serializedConfiguration: string): HostConfig {
    var obj = JSON.parse(serializedConfiguration);

    return obj ? Object.assign(new HostConfig(), {
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
    }) : null;
}