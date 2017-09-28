import * as Enums from "./enums";
export interface ISpacingDefinition {
    left: number;
    top: number;
    right: number;
    bottom: number;
}
export interface IPaddingDefinition {
    top: Enums.Padding;
    right: Enums.Padding;
    bottom: Enums.Padding;
    left: Enums.Padding;
}
export interface ITextColorDefinition {
    normal: string;
    subtle: string;
}
export interface IContainerStyleDefinition {
    backgroundColor?: string;
    fontColors: {
        default: ITextColorDefinition;
        accent: ITextColorDefinition;
        good: ITextColorDefinition;
        warning: ITextColorDefinition;
        attention: ITextColorDefinition;
    };
}
export interface IAdaptiveCardConfig {
    allowCustomStyle: boolean;
}
export interface IImageConfig {
    size: Enums.Size;
}
export interface IImageSetConfig {
    imageSize: Enums.Size;
    maxImageHeight: number;
}
export interface IFactTextDefinition {
    size: Enums.TextSize;
    color: Enums.TextColor;
    isSubtle: boolean;
    weight: Enums.TextWeight;
    wrap: boolean;
}
export interface IFactTitleDefinition extends IFactTextDefinition {
    maxWidth?: number;
}
export interface IFactSetConfig {
    title: IFactTitleDefinition;
    value: IFactTextDefinition;
    spacing: number;
}
export interface IShowCardActionConfig {
    actionMode: Enums.ShowCardActionMode;
    inlineTopMargin: number;
    style?: Enums.ContainerStyle;
}
export interface IActionsConfig {
    maxActions: number;
    spacing: Enums.Spacing;
    buttonSpacing: number;
    showCard: IShowCardActionConfig;
    actionsOrientation: Enums.Orientation;
    actionAlignment: Enums.ActionAlignment;
}
export interface IHostConfig {
    supportsInteractivity: boolean;
    fontFamily?: string;
    fontSizes: {
        small: number;
        default: number;
        medium: number;
        large: number;
        extraLarge: number;
    };
    fontWeights: {
        lighter: number;
        default: number;
        bolder: number;
    };
    imageSizes: {
        small: number;
        medium: number;
        large: number;
    };
    containerStyles: {
        default: IContainerStyleDefinition;
        emphasis: IContainerStyleDefinition;
    };
    spacing: {
        small: number;
        default: number;
        medium: number;
        large: number;
        extraLarge: number;
        padding: number;
    };
    separator: {
        lineThickness: number;
        lineColor: string;
    };
    actions: IActionsConfig;
    adaptiveCard: IAdaptiveCardConfig;
    image: IImageConfig;
    imageSet: IImageSetConfig;
    factSet: IFactSetConfig;
}
export declare function parseHostConfig(serializedConfiguration: string): IHostConfig;
