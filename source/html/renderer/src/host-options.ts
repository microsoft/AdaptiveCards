import * as Enums from "./enums";

export interface ISpacingDefinition {
    left: number,
    top: number,
    right: number,
    bottom: number
}

export interface IColorDefinition {
    normal: string,
    subtle: string
}

export interface ISeparationDefinition {
    spacing: number,
    lineThickness?: number,
    lineColor?: string
}

export interface ITextBlockConfiguration {
    separations: {
        small: ISeparationDefinition,
        normal: ISeparationDefinition,
        medium: ISeparationDefinition,
        large: ISeparationDefinition,
        extraLarge: ISeparationDefinition,
    }    
}

export interface IContainerStyleDefinition {
    backgroundColor?: string,
    padding?: ISpacingDefinition,
    borderColor?: string,
    borderThickness?: ISpacingDefinition
}

export interface IContainerConfiguration {
    separation: ISeparationDefinition,
    normal: IContainerStyleDefinition,
    emphasis: IContainerStyleDefinition
}

export interface IImageConfiguration {
    separation: ISeparationDefinition
    size: Enums.Size
}

export interface IImageSetConfiguration {
    separation: ISeparationDefinition
    imageSize: Enums.Size
}

export interface ITextFormatDefinition {
    size: Enums.TextSize,
    color: Enums.TextColor,
    isSubtle: boolean,
    weight: Enums.TextWeight    
}

export interface IFactSetConfiguration {
    separation: ISeparationDefinition,
    title: ITextFormatDefinition,
    value: ITextFormatDefinition,
    spacing: number
}

export interface IColumnSetConfiguration {
    separation: ISeparationDefinition
}

export interface IColumnConfiguration {
    separation: ISeparationDefinition
}

export interface IShowCardActionConfiguration {
    actionMode: Enums.ShowCardActionMode,
    inlineCardSpacing: number,
    backgroundColor: string,
    padding: ISpacingDefinition
}

export interface IActionsConfiguration {
    maxActions: number,
    supportedActionTypes: Array<any>,
    separation: ISeparationDefinition,
    buttonSpacing: number,
    stretch: boolean,
    showCard: IShowCardActionConfiguration
}

export interface IInputConfiguration {
    separation: ISeparationDefinition
}

export interface IAdaptiveCardConfiguration {
    supportedElementTypes: Array<any>,
    supportsInteractivity: boolean,
    padding: ISpacingDefinition,
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
    backgroundColor: string,
    colors: {
        dark: IColorDefinition,
        light: IColorDefinition,
        accent: IColorDefinition,
        good: IColorDefinition,
        warning: IColorDefinition,
        attention: IColorDefinition
    },
    strongSeparation: ISeparationDefinition,
    container: IContainerConfiguration,
    textBlock: ITextBlockConfiguration,
    image: IImageConfiguration,
    imageSet: IImageSetConfiguration,
    factSet: IFactSetConfiguration,
    columnSet: IColumnSetConfiguration,
    column: IColumnConfiguration,
    actions: IActionsConfiguration,
    input: IInputConfiguration
}