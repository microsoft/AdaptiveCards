import * as Enums from "./enums";
import * as Utils from "./utils";

export interface ISpacingDefinition {
    left: number,
    top: number,
    right: number,
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

export interface IPaddingDefinition {
    top: Enums.Padding,
    right: Enums.Padding,
    bottom: Enums.Padding,
    left: Enums.Padding
}

function parsePaddingDefinition(obj: any): IPaddingDefinition {
    return obj ? {
        top: Utils.getValueOrDefault<Enums.Padding>(obj["top"], "none"),
        right: Utils.getValueOrDefault<Enums.Padding>(obj["right"], "none"),
        bottom: Utils.getValueOrDefault<Enums.Padding>(obj["bottom"], "none"),
        left: Utils.getValueOrDefault<Enums.Padding>(obj["left"], "none")
    } : null;
}

export interface ITextColorDefinition {
    normal: string,
    subtle: string
}

function parseTextColorDefinition(obj: any): ITextColorDefinition {
    return obj ? {
        normal: obj["normal"],
        subtle: obj["subtle"]
    } : null;
}

export interface IContainerStyleDefinition {
    backgroundColor?: string,
    fontColors: {
        dark: ITextColorDefinition,
        light: ITextColorDefinition,
        accent: ITextColorDefinition,
        good: ITextColorDefinition,
        warning: ITextColorDefinition,
        attention: ITextColorDefinition
    },
}

function parseColorPaletteDefinition(obj: any): IContainerStyleDefinition {
    return obj ? {
        backgroundColor: obj["backgroundColor"],
        fontColors: {
            dark: parseTextColorDefinition(obj["fontColors"]["dark"]),
            light: parseTextColorDefinition(obj["fontColors"]["light"]),
            accent: parseTextColorDefinition(obj["fontColors"]["accent"]),
            good: parseTextColorDefinition(obj["fontColors"]["good"]),
            warning: parseTextColorDefinition(obj["fontColors"]["warning"]),
            attention: parseTextColorDefinition(obj["fontColors"]["attention"])
        }
    } : null;
}

export interface IAdaptiveCardConfig {
    allowCustomStyle: boolean
}

function parseAdaptiveCardConfiguration(obj: any): IAdaptiveCardConfig {
    return obj ? {
        allowCustomStyle: obj["allowCustomStyle"]
    } : null;
}

export interface ITextBlockConfig {
    color: Enums.TextColor
}

function parseTextBlockConfiguration(obj: any): ITextBlockConfig {
    return obj ? {
        color: obj["color"]
    } : null;
}

export interface IImageConfig {
    size: Enums.Size
}

function parseImageConfiguration(obj: any): IImageConfig {
    return obj ? {
        size: obj["size"]
    } : null;
}

export interface IImageSetConfig {
    imageSize: Enums.Size
    maxImageHeight: number
}

function parseImageSetConfiguration(obj: any): IImageSetConfig {
    return obj ? {
        imageSize: obj["imageSize"],
        maxImageHeight: Utils.getValueOrDefault<number>("maxImageHeight", 100)
    } : null;
}

export interface IFactTextDefinition {
    size: Enums.TextSize,
    color: Enums.TextColor,
    isSubtle: boolean,
    weight: Enums.TextWeight,
    wrap: boolean    
}

function parseFactTextDefinition(obj: any): IFactTextDefinition {
    return obj ? {
        size: Utils.getValueOrDefault<Enums.TextSize>(obj["size"], "normal"),
        color: Utils.getValueOrDefault<Enums.TextColor>(obj["color"], "dark"),
        isSubtle: obj["isSubtle"],
        weight: Utils.getValueOrDefault<Enums.TextWeight>(obj["weight"], "normal"),
        wrap: obj["wrap"]
    } : null;
}

export interface IFactTitleDefinition extends IFactTextDefinition {
    maxWidth?: number;
}

function parseFactTitleDefinition(obj: any): IFactTitleDefinition {
    var result: IFactTitleDefinition = parseFactTextDefinition(obj);

    if (result) {
        result.maxWidth = obj["maxWidth"];
    }

    return result;
}

export interface IFactSetConfig {
    title: IFactTitleDefinition,
    value: IFactTextDefinition,
    spacing: number
}

function parseFactSetConfiguration(obj: any): IFactSetConfig {
    return obj ? {
        title: parseFactTitleDefinition(obj["title"]),
        value: parseFactTextDefinition(obj["value"]),
        spacing: obj["spacing"]
    } : null;
}

export interface IShowCardActionConfig {
    actionMode: Enums.ShowCardActionMode,
    inlineTopMargin: number,
    style?: Enums.ContainerStyle
}

function parseShowCardActionConfiguration(obj: any): IShowCardActionConfig {
    return obj ? {
        actionMode: Utils.getValueOrDefault<Enums.ShowCardActionMode>(obj["actionMode"], "inlineEdgeToEdge"),
        inlineTopMargin: obj["inlineTopMargin"],
        style: Utils.getValueOrDefault<Enums.ContainerStyle>(obj["style"], "emphasis")
    } : null;
}

export interface IActionsConfig {
    maxActions: number,
    spacing: Enums.Spacing,
    buttonSpacing: number,
    showCard: IShowCardActionConfig,
    preExpandSingleShowCardAction?: boolean,    
    actionsOrientation: Enums.Orientation,
    actionAlignment: Enums.ActionAlignment
}

function parseActionsConfiguration(obj: any): IActionsConfig {
    return obj ? {
        maxActions: obj["maxActions"],
        spacing: Utils.getValueOrDefault<Enums.Spacing>(obj["spacing"], "default"),
        buttonSpacing: obj["buttonSpacing"],
        showCard: parseShowCardActionConfiguration(obj["showCard"]),
        preExpandSingleShowCardAction: Utils.getValueOrDefault<boolean>(obj["preExpandSingleShowCardAction"], false),
        actionsOrientation: Utils.getValueOrDefault<Enums.Orientation>(obj["actionsOrientation"], "horizontal"),
        actionAlignment: Utils.getValueOrDefault<Enums.ActionAlignment>(obj["actionAlignment"], "left"),
    } : null;
}

export interface IHostConfig {
    supportsInteractivity: boolean,
    fontFamily?: string,
    fontSizes: {
        small: number,
        normal: number,
        medium: number,
        large: number,
        extraLarge: number
    },
    fontWeights: {
        lighter: number,
        normal: number,
        bolder: number
    },
    imageSizes: {
        small: number,
        medium: number,
        large: number
    }
    containerStyles: {
        default: IContainerStyleDefinition,
        emphasis: IContainerStyleDefinition
    },
    spacing: {
        small: number,
        default: number,
        medium: number,
        large: number,
        extraLarge: number,
        padding: number
    },
    separator: {
        lineThickness: number,
        lineColor: string        
    }
    actions: IActionsConfig,
    adaptiveCard: IAdaptiveCardConfig,
    textBlock: ITextBlockConfig,
    image: IImageConfig,
    imageSet: IImageSetConfig,
    factSet: IFactSetConfig
}

export function parseHostConfig(serializedConfiguration: string): IHostConfig {
    var obj = JSON.parse(serializedConfiguration);

    return obj ? {
        supportsInteractivity: obj["supportsInteractivity"],
        fontFamily: obj["fontFamily"],
        fontSizes: {
            small: obj["fontSizes"]["small"],
            normal: obj["fontSizes"]["normal"],
            medium: obj["fontSizes"]["medium"],
            large: obj["fontSizes"]["large"],
            extraLarge: obj["fontSizes"]["extraLarge"]
        },
        fontWeights: {
            lighter: obj["fontWeights"]["lighter"],
            normal: obj["fontWeights"]["normal"],
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
        textBlock: parseTextBlockConfiguration(obj["textBlock"]),
        image: parseImageConfiguration(obj["image"]),
        imageSet: parseImageSetConfiguration(obj["imageSet"]),
        factSet: parseFactSetConfiguration(obj["factSet"])
    } : null;
}