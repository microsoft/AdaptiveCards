import * as Enums from "./enums";

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

export interface IColorDefinition {
    normal: string,
    subtle: string
}

function parseColorDefinition(obj: any): IColorDefinition {
    return obj ? {
        normal: obj["normal"],
        subtle: obj["subtle"]
    } : null;
}

export interface ISeparationDefinition {
    spacing: number,
    lineThickness?: number,
    lineColor?: string
}

function parseSeparationDefinition(obj: any): ISeparationDefinition {
    return obj ? {
        spacing: obj["spacing"],
        lineThickness: obj["lineThickness"],
        lineColor: obj["lineColor"]
    } : null;
}

export interface IAdaptiveCardConfig {
    backgroundColor: string,
    padding: ISpacingDefinition
}

function parseAdaptiveCardConfiguration(obj: any): IAdaptiveCardConfig {
    return obj ? {
        backgroundColor: obj["backgroundColor"],
        padding: parseSpacingDefinition(obj["padding"])
    } : null;
}

export interface ITextBlockConfig {
    color: Enums.TextColor,
    separations: {
        small: ISeparationDefinition,
        normal: ISeparationDefinition,
        medium: ISeparationDefinition,
        large: ISeparationDefinition,
        extraLarge: ISeparationDefinition,
    }    
}

function parseTextBlockConfiguration(obj: any): ITextBlockConfig {
    return obj ? {
        color: obj["color"],
        separations: {
            small: parseSeparationDefinition(obj["separations"]["small"]),
            normal: parseSeparationDefinition(obj["separations"]["normal"]),
            medium: parseSeparationDefinition(obj["separations"]["medium"]),
            large: parseSeparationDefinition(obj["separations"]["large"]),
            extraLarge: parseSeparationDefinition(obj["separations"]["extraLarge"])
        }
    } : null;
}

export interface IContainerStyleDefinition {
    backgroundColor?: string,
    padding?: ISpacingDefinition,
    borderColor?: string,
    borderThickness?: ISpacingDefinition
}

function parseContainerStyleDefinition(obj: any): IContainerStyleDefinition {
    return obj ? {
        backgroundColor: obj["backgroundColor"],
        padding: parseSpacingDefinition(obj["padding"]),
        borderColor: obj["borderColor"],
        borderThickness: obj["borderThickness"]
    } : null;
}

export interface IContainerConfig {
    separation: ISeparationDefinition,
    normal: IContainerStyleDefinition,
    emphasis: IContainerStyleDefinition
}

function parseContainerConfiguration(obj: any): IContainerConfig {
    return obj ? {
        separation: parseSeparationDefinition(obj["separation"]),
        normal: parseContainerStyleDefinition(obj["normal"]),
        emphasis: parseContainerStyleDefinition(obj["emphasis"])
    } : null;
}

export interface IImageConfig {
    separation: ISeparationDefinition
    size: Enums.Size
}

function parseImageConfiguration(obj: any): IImageConfig {
    return obj ? {
        separation: parseSeparationDefinition(obj["separation"]),
        size: obj["size"]
    } : null;
}

export interface IImageSetConfig {
    separation: ISeparationDefinition
    imageSize: Enums.Size
}

function parseImageSetConfiguration(obj: any): IImageSetConfig {
    return obj ? {
        separation: parseSeparationDefinition(obj["separation"]),
        imageSize: obj["imageSize"]
    } : null;
}

export interface ITextFormatDefinition {
    size: Enums.TextSize,
    color: Enums.TextColor,
    isSubtle: boolean,
    weight: Enums.TextWeight    
}

function parseTextFormatDefinition(obj: any): ITextFormatDefinition {
    return obj ? {
        size: obj["size"],
        color: obj["color"],
        isSubtle: obj["isSubtle"],
        weight: obj["weight"]
    } : null;
}

export interface IFactSetConfig {
    separation: ISeparationDefinition,
    title: ITextFormatDefinition,
    value: ITextFormatDefinition,
    spacing: number
}

function parseFactSetConfiguration(obj: any): IFactSetConfig {
    return obj ? {
        separation: parseSeparationDefinition(obj["separation"]),
        title: parseTextFormatDefinition(obj["title"]),
        value: parseTextFormatDefinition(obj["value"]),
        spacing: obj["spacing"]
    } : null;
}

export interface IColumnSetConfig {
    separation: ISeparationDefinition
}

function parseColumnSetConfiguration(obj: any): IColumnSetConfig {
    return obj ? {
        separation: parseSeparationDefinition(obj["separation"])
    } : null;
}

export interface IColumnConfig {
    separation: ISeparationDefinition
}

function parseColumnConfiguration(obj: any): IColumnConfig {
    return obj ? {
        separation: parseSeparationDefinition(obj["separation"])
    } : null;
}

export interface IShowCardActionConfig {
    actionMode: Enums.ShowCardActionMode,
    inlineCardSpacing: number,
    backgroundColor: string,
    padding: ISpacingDefinition
}

function parseShowCardActionConfiguration(obj: any): IShowCardActionConfig {
    return obj ? {
        actionMode: obj["actionMode"],
        inlineCardSpacing: obj["inlineCardSpacing"],
        backgroundColor: obj["backgroundColor"],
        padding: parseSpacingDefinition(obj["padding"])
    } : null;
}

export interface IActionsConfig {
    maxActions: number,
    supportedActionTypes?: Array<string>,
    separation: ISeparationDefinition,
    buttonSpacing: number,
    stretch: boolean,
    showCard: IShowCardActionConfig,
    actionsOrientation: Enums.Orientation,
    actionAlignment: Enums.HorizontalAlignment
}

function parseActionsConfiguration(obj: any): IActionsConfig {
    return obj ? {
        maxActions: obj["maxActions"],
        supportedActionTypes: obj["supportedActionTypes"],
        separation: parseSeparationDefinition(obj["separation"]),
        buttonSpacing: obj["buttonSpacing"],
        stretch: obj["stretch"],
        showCard: parseShowCardActionConfiguration(obj["showCard"]),
        actionsOrientation: obj["actionsOrientation"],
        actionAlignment: obj["actionAlignment"]
    } : null;
}

export interface IInputConfig {
    separation: ISeparationDefinition
}

function parseInputConfiguration(obj: any): IInputConfig {
    return obj ? {
        separation: parseSeparationDefinition(obj["separation"])
    } : null;
}

export interface IHostConfig {
    supportedElementTypes?: Array<string>,
    supportsInteractivity: boolean,
    fontFamily: string,
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
    colors: {
        dark: IColorDefinition,
        light: IColorDefinition,
        accent: IColorDefinition,
        good: IColorDefinition,
        warning: IColorDefinition,
        attention: IColorDefinition
    },
    strongSeparation: ISeparationDefinition,
    actions: IActionsConfig,
    adaptiveCard: IAdaptiveCardConfig,
    container: IContainerConfig,
    textBlock: ITextBlockConfig,
    image: IImageConfig,
    imageSet: IImageSetConfig,
    factSet: IFactSetConfig,
    column: IColumnConfig,
    columnSet: IColumnSetConfig,
    input: IInputConfig
}

export function parseHostConfig(serializedConfiguration: string): IHostConfig {
    var obj = JSON.parse(serializedConfiguration);

    return obj ? {
        supportedElementTypes: obj["supportedElementTypes"],
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
        colors: {
            dark: parseColorDefinition(obj["colors"]["dark"]),
            light: parseColorDefinition(obj["colors"]["light"]),
            accent: parseColorDefinition(obj["colors"]["accent"]),
            good: parseColorDefinition(obj["colors"]["good"]),
            warning: parseColorDefinition(obj["colors"]["warning"]),
            attention: parseColorDefinition(obj["colors"]["attention"])
        },        
        strongSeparation: parseSeparationDefinition(obj["strongSeparation"]),
        actions: parseActionsConfiguration(obj["actions"]),
        adaptiveCard: parseAdaptiveCardConfiguration(obj["adaptiveCard"]),
        container: parseContainerConfiguration(obj["container"]),
        textBlock: parseTextBlockConfiguration(obj["textBlock"]),
        image: parseImageConfiguration(obj["image"]),
        imageSet: parseImageSetConfiguration(obj["imageSet"]),
        factSet: parseFactSetConfiguration(obj["factSet"]),
        column: parseColumnConfiguration(obj["column"]),
        columnSet: parseColumnSetConfiguration(obj["columnSet"]),
        input: parseInputConfiguration(obj["input"])
    } : null;
}