import * as Enums from "./enums";
export declare class SpacingDefinition {
    left: number;
    top: number;
    right: number;
    bottom: number;
    constructor(obj?: any);
}
export declare class PaddingDefinition {
    top: Enums.Padding;
    right: Enums.Padding;
    bottom: Enums.Padding;
    left: Enums.Padding;
    constructor(obj?: any);
    toJSON(): {
        top: string;
        right: string;
        bottom: string;
        left: string;
    };
}
export declare class TextColorDefinition {
    normal: string;
    subtle: string;
    constructor(obj?: any);
}
export declare class ContainerStyleDefinition {
    backgroundColor?: string;
    readonly fontColors: {
        default: TextColorDefinition;
        accent: TextColorDefinition;
        good: TextColorDefinition;
        warning: TextColorDefinition;
        attention: TextColorDefinition;
    };
    constructor(obj?: any);
}
export declare class AdaptiveCardConfig {
    allowCustomStyle: boolean;
    constructor(obj?: any);
}
export declare class ImageConfig {
    size: Enums.Size;
    constructor(obj?: any);
    toJSON(): {
        size: string;
    };
}
export declare class ImageSetConfig {
    imageSize: Enums.Size;
    maxImageHeight: number;
    constructor(obj?: any);
    toJSON(): {
        imageSize: string;
        maxImageHeight: number;
    };
}
export declare class FactTextDefinition {
    size: Enums.TextSize;
    color: Enums.TextColor;
    isSubtle: boolean;
    weight: Enums.TextWeight;
    wrap: boolean;
    constructor(obj?: any);
    toJSON(): any;
}
export declare class FactTitleDefinition extends FactTextDefinition {
    maxWidth?: number;
    weight: Enums.TextWeight;
    constructor(obj?: any);
}
export declare class FactSetConfig {
    readonly title: FactTitleDefinition;
    readonly value: FactTextDefinition;
    spacing: number;
    constructor(obj?: any);
}
export declare class ShowCardActionConfig {
    actionMode: Enums.ShowCardActionMode;
    inlineTopMargin: number;
    style?: Enums.ContainerStyle;
    constructor(obj?: any);
    toJSON(): {
        actionMode: string;
        inlineTopMargin: number;
        style: string;
    };
}
export declare class ActionsConfig {
    maxActions: number;
    spacing: Enums.Spacing;
    buttonSpacing: number;
    readonly showCard: ShowCardActionConfig;
    preExpandSingleShowCardAction?: boolean;
    actionsOrientation: Enums.Orientation;
    actionAlignment: Enums.ActionAlignment;
    constructor(obj?: any);
    toJSON(): {
        maxActions: number;
        spacing: string;
        buttonSpacing: number;
        showCard: ShowCardActionConfig;
        preExpandSingleShowCardAction: boolean;
        actionsOrientation: string;
        actionAlignment: string;
    };
}
export declare class ContainerStyleSet {
    readonly default: ContainerStyleDefinition;
    readonly emphasis: ContainerStyleDefinition;
    constructor(obj?: any);
}
export declare class HostConfig {
    supportsInteractivity: boolean;
    fontFamily?: string;
    readonly fontSizes: {
        small: number;
        default: number;
        medium: number;
        large: number;
        extraLarge: number;
    };
    readonly fontWeights: {
        lighter: number;
        default: number;
        bolder: number;
    };
    readonly imageSizes: {
        small: number;
        medium: number;
        large: number;
    };
    readonly containerStyles: ContainerStyleSet;
    readonly spacing: {
        small: number;
        default: number;
        medium: number;
        large: number;
        extraLarge: number;
        padding: number;
    };
    readonly separator: {
        lineThickness: number;
        lineColor: string;
    };
    readonly actions: ActionsConfig;
    readonly adaptiveCard: AdaptiveCardConfig;
    readonly image: ImageConfig;
    readonly imageSet: ImageSetConfig;
    readonly factSet: FactSetConfig;
    constructor(obj?: any);
    getEffectiveSpacing(spacing: Enums.Spacing): number;
    getEffectivePadding(padding: Enums.Padding): number;
    paddingToSpacingDefinition(padding: PaddingDefinition): SpacingDefinition;
    getContainerStyleDefinition(containerStyle: Enums.ContainerStyle): ContainerStyleDefinition;
}
