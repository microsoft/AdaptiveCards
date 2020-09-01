// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";
import * as Utils from "./utils";
import * as Shared from "./shared";
import { HostCapabilities } from "./host-capabilities";

function parseHostConfigEnum(targetEnum: { [s: number]: string }, value: string | number, defaultValue: number): number {
    if (typeof value === "string") {
        let parsedValue = Utils.parseEnum(targetEnum, value, defaultValue);

        return parsedValue !== undefined ? parsedValue : defaultValue;
    }
    else if (typeof value === "number") {
        return value;
    }
    else {
        return defaultValue;
    }
}

export class ColorDefinition {
    default: string = "#000000";
    subtle: string = "#666666";

    constructor(defaultColor?: string, subtleColor?: string) {
        if (defaultColor) {
            this.default = defaultColor;
        }

        if (subtleColor) {
            this.subtle = subtleColor;
        }
    }

    parse(obj?: any) {
        if (obj) {
            this.default = obj["default"] || this.default;
            this.subtle = obj["subtle"] || this.subtle;
        }
    }
}

export class TextColorDefinition extends ColorDefinition {
    readonly highlightColors = new ColorDefinition("#22000000", "#11000000");

    parse(obj?: any) {
        super.parse(obj);

        if (obj) {
            this.highlightColors.parse(obj["highlightColors"]);
        }
    }
}

export class AdaptiveCardConfig {
    allowCustomStyle: boolean = false;

    constructor(obj?: any) {
        if (obj) {
            this.allowCustomStyle = obj["allowCustomStyle"] || this.allowCustomStyle;
        }
    }
}

export class ImageSetConfig {
    imageSize: Enums.Size = Enums.Size.Medium;
    maxImageHeight: number = 100;

    constructor(obj?: any) {
        if (obj) {
            this.imageSize = obj["imageSize"] != null ? obj["imageSize"] : this.imageSize;
            this.maxImageHeight = <number>Utils.parseNumber(obj["maxImageHeight"], 100);
        }
    }

    toJSON() {
        return {
            imageSize: Enums.Size[this.imageSize],
            maxImageHeight: this.maxImageHeight
        }
    }
}

export class MediaConfig {
    defaultPoster?: string;
    allowInlinePlayback: boolean = true;

    constructor(obj?: any) {
        if (obj) {
            this.defaultPoster = obj["defaultPoster"];
            this.allowInlinePlayback = obj["allowInlinePlayback"] || this.allowInlinePlayback;
        }
    }

    toJSON() {
        return {
            defaultPoster: this.defaultPoster,
            allowInlinePlayback: this.allowInlinePlayback
        }
    }
}

export class BaseTextDefinition {
    size: Enums.TextSize = Enums.TextSize.Default;
    color: Enums.TextColor = Enums.TextColor.Default;;
    isSubtle: boolean = false;
    weight: Enums.TextWeight = Enums.TextWeight.Default;

    constructor(obj?: any) {
        if (obj) {
            this.size = parseHostConfigEnum(Enums.TextSize, obj["size"], this.size);
            this.color = parseHostConfigEnum(Enums.TextColor, obj["color"], this.color);
            this.isSubtle = obj["isSubtle"] || this.isSubtle;
            this.weight = parseHostConfigEnum(Enums.TextWeight, obj["weight"], this.getDefaultWeight());
        }
    }

    getDefaultWeight() {
        return Enums.TextWeight.Default;
    }

    toJSON(): any {
        return {
            size: Enums.TextSize[this.size],
            color: Enums.TextColor[this.color],
            isSubtle: this.isSubtle,
            weight: Enums.TextWeight[this.weight]
        }
    }
}

export class RequiredInputLabelTextDefinition extends BaseTextDefinition {
    suffix?: string = " *";
    suffixColor: Enums.TextColor = Enums.TextColor.Attention;

    constructor(obj?: any) {
        super(obj);

        if (obj) {
            this.suffix = obj["suffix"] || this.suffix;
            this.suffixColor = parseHostConfigEnum(Enums.TextColor, obj["suffixColor"], this.suffixColor);
        }
    }

    toJSON(): any {
        let result = super.toJSON();
        result["suffix"] = this.suffix;
        result["suffixColor"] = Enums.TextColor[this.suffixColor];

        return result;
    }
}

export class InputLabelConfig {
    inputSpacing: Enums.Spacing = Enums.Spacing.Small;
    readonly requiredInputs: RequiredInputLabelTextDefinition = new RequiredInputLabelTextDefinition();
    readonly optionalInputs: BaseTextDefinition = new BaseTextDefinition();

    constructor(obj?: any) {
        if (obj) {
            this.inputSpacing = parseHostConfigEnum(Enums.Spacing, obj["inputSpacing"], this.inputSpacing);
            this.requiredInputs = new RequiredInputLabelTextDefinition(obj["requiredInputs"]);
            this.optionalInputs = new BaseTextDefinition(obj["optionalInputs"]);
        }
    }
}

export class InputConfig {
    readonly label: InputLabelConfig = new InputLabelConfig();
    readonly errorMessage: BaseTextDefinition = new BaseTextDefinition({ color: Enums.TextColor.Attention });

    constructor(obj?: any) {
        if (obj) {
            this.label = new InputLabelConfig(obj["label"]);
            this.errorMessage = new BaseTextDefinition(obj["errorMessage"]);
        }
    }
}

export class FactTextDefinition extends BaseTextDefinition {
    wrap: boolean = true;

    constructor(obj?: any) {
        super(obj);

        if (obj) {
            this.wrap = obj["wrap"] != null ? obj["wrap"] : this.wrap;
        }
    }

    toJSON(): any {
        let result = super.toJSON();
        result["wrap"] = this.wrap;

        return result;
    }
}

export class FactTitleDefinition extends FactTextDefinition {
    maxWidth?: number = 150;
    weight: Enums.TextWeight = Enums.TextWeight.Bolder;

    constructor(obj?: any) {
        super(obj);

        if (obj) {
            this.maxWidth = obj["maxWidth"] != null ? obj["maxWidth"] : this.maxWidth;
            this.weight = parseHostConfigEnum(Enums.TextWeight, obj["weight"], Enums.TextWeight.Bolder);
        }
    }

    getDefaultWeight() {
        return Enums.TextWeight.Bolder;
    }
}

export class FactSetConfig {
    readonly title: FactTitleDefinition = new FactTitleDefinition();
    readonly value: FactTextDefinition = new FactTextDefinition();
    spacing: number = 10;

    constructor(obj?: any) {
        if (obj) {
            this.title = new FactTitleDefinition(obj["title"]);
            this.value = new FactTextDefinition(obj["value"]);
            this.spacing = obj.spacing && obj.spacing != null ? obj.spacing && obj.spacing : this.spacing;
        }
    }
}

export class ShowCardActionConfig {
    actionMode: Enums.ShowCardActionMode = Enums.ShowCardActionMode.Inline;
    inlineTopMargin: number = 16;
    style?: string = Enums.ContainerStyle.Emphasis;

    constructor(obj?: any) {
        if (obj) {
            this.actionMode = parseHostConfigEnum(Enums.ShowCardActionMode, obj["actionMode"], Enums.ShowCardActionMode.Inline);
            this.inlineTopMargin = obj["inlineTopMargin"] != null ? obj["inlineTopMargin"] : this.inlineTopMargin;
            this.style = obj["style"] && typeof obj["style"] === "string" ? obj["style"] : Enums.ContainerStyle.Emphasis;
        }
    }

    toJSON() {
        return {
            actionMode: Enums.ShowCardActionMode[this.actionMode],
            inlineTopMargin: this.inlineTopMargin,
            style: this.style
        }
    }
}

export class ActionsConfig {
    maxActions: number = 5;
    spacing: Enums.Spacing = Enums.Spacing.Default;
    buttonSpacing: number = 20;
    readonly showCard: ShowCardActionConfig = new ShowCardActionConfig();
    preExpandSingleShowCardAction?: boolean = false;
    actionsOrientation: Enums.Orientation = Enums.Orientation.Horizontal;
    actionAlignment: Enums.ActionAlignment = Enums.ActionAlignment.Left;
    iconPlacement: Enums.ActionIconPlacement = Enums.ActionIconPlacement.LeftOfTitle;
    allowTitleToWrap: boolean = false;
    iconSize: number = 16;

    constructor(obj?: any) {
        if (obj) {
            this.maxActions = obj["maxActions"] != null ? obj["maxActions"] : this.maxActions;
            this.spacing = parseHostConfigEnum(Enums.Spacing, obj.spacing && obj.spacing, Enums.Spacing.Default);
            this.buttonSpacing = obj["buttonSpacing"] != null ? obj["buttonSpacing"] : this.buttonSpacing;
            this.showCard = new ShowCardActionConfig(obj["showCard"]);
            this.preExpandSingleShowCardAction = Utils.parseBool(obj["preExpandSingleShowCardAction"], false);
            this.actionsOrientation = parseHostConfigEnum(Enums.Orientation, obj["actionsOrientation"], Enums.Orientation.Horizontal);
            this.actionAlignment = parseHostConfigEnum(Enums.ActionAlignment, obj["actionAlignment"], Enums.ActionAlignment.Left);
            this.iconPlacement = parseHostConfigEnum(Enums.ActionIconPlacement, obj["iconPlacement"], Enums.ActionIconPlacement.LeftOfTitle);
            this.allowTitleToWrap = obj["allowTitleToWrap"] != null ? obj["allowTitleToWrap"] : this.allowTitleToWrap;

            try {
                let sizeAndUnit = Shared.SizeAndUnit.parse(obj["iconSize"]);

                if (sizeAndUnit.unit == Enums.SizeUnit.Pixel) {
                    this.iconSize = sizeAndUnit.physicalSize;
                }
            }
            catch (e) {
                // Swallow this, keep default icon size
            }
        }
    }

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

export class ColorSetDefinition {
    private parseSingleColor(obj: any, propertyName: string) {
        if (obj) {
            ((<any>this)[propertyName] as TextColorDefinition).parse(obj[propertyName]);
        }
    }

    default: TextColorDefinition = new TextColorDefinition();
    dark: TextColorDefinition = new TextColorDefinition();
    light: TextColorDefinition = new TextColorDefinition();
    accent: TextColorDefinition = new TextColorDefinition();
    good: TextColorDefinition = new TextColorDefinition();
    warning: TextColorDefinition = new TextColorDefinition();
    attention: TextColorDefinition = new TextColorDefinition();

    constructor(obj?: any) {
        this.parse(obj);
    }

    parse(obj: any) {
        if (obj) {
            this.parseSingleColor(obj, "default");
            this.parseSingleColor(obj, "dark");
            this.parseSingleColor(obj, "light");
            this.parseSingleColor(obj, "accent");
            this.parseSingleColor(obj, "good");
            this.parseSingleColor(obj, "warning");
            this.parseSingleColor(obj, "attention");
        }
    }
}

export class ContainerStyleDefinition {
    backgroundColor?: string;

    readonly foregroundColors: ColorSetDefinition = new ColorSetDefinition(
        {
            "default": { default: "#333333", subtle: "#EE333333" },
            "dark": { default: "#000000", subtle: "#66000000" },
            "light": { default: "#FFFFFF", subtle: "#33000000" },
            "accent": { default: "#2E89FC", subtle: "#882E89FC" },
            "good": { default: "#028A02", subtle: "#DD027502" },
            "warning": { default: "#E69500", subtle: "#DDE69500" },
            "attention": { default: "#CC3300", subtle: "#DDCC3300" }
        }
    );

    highlightBackgroundColor?: string;
    highlightForegroundColor?: string;

    parse(obj: any) {
        if (obj) {
            this.backgroundColor = obj["backgroundColor"];

            this.foregroundColors.parse(obj["foregroundColors"]);

            this.highlightBackgroundColor = obj["highlightBackgroundColor"];
            this.highlightForegroundColor = obj["highlightForegroundColor"];
        }
    }

    constructor(obj?: any) {
        this.parse(obj);
    }

    get isBuiltIn(): boolean {
        return false;
    }
}

class BuiltInContainerStyleDefinition extends ContainerStyleDefinition {
    get isBuiltIn(): boolean {
        return true;
    }
}

export interface ILineHeightDefinitions {
    small: number;
    medium: number;
    default: number;
    large: number;
    extraLarge: number;
}

export class ContainerStyleSet {
    private _allStyles: { [key: string]: ContainerStyleDefinition } = {};

    constructor(obj?: any) {
        this._allStyles[Enums.ContainerStyle.Default] = new BuiltInContainerStyleDefinition();
        this._allStyles[Enums.ContainerStyle.Emphasis] = new BuiltInContainerStyleDefinition();
        this._allStyles[Enums.ContainerStyle.Accent] = new BuiltInContainerStyleDefinition();
        this._allStyles[Enums.ContainerStyle.Good] = new BuiltInContainerStyleDefinition();
        this._allStyles[Enums.ContainerStyle.Attention] = new BuiltInContainerStyleDefinition();
        this._allStyles[Enums.ContainerStyle.Warning] = new BuiltInContainerStyleDefinition();

        if (obj) {
            this._allStyles[Enums.ContainerStyle.Default].parse(obj[Enums.ContainerStyle.Default]);
            this._allStyles[Enums.ContainerStyle.Emphasis].parse(obj[Enums.ContainerStyle.Emphasis]);
            this._allStyles[Enums.ContainerStyle.Accent].parse(obj[Enums.ContainerStyle.Accent]);
            this._allStyles[Enums.ContainerStyle.Good].parse(obj[Enums.ContainerStyle.Good]);
            this._allStyles[Enums.ContainerStyle.Attention].parse(obj[Enums.ContainerStyle.Attention]);
            this._allStyles[Enums.ContainerStyle.Warning].parse(obj[Enums.ContainerStyle.Warning]);

            const customStyleArray = obj["customStyles"];

            if (customStyleArray && Array.isArray(customStyleArray)) {
                for (let customStyle of customStyleArray) {
                    if (customStyle) {
                        let styleName = customStyle["name"];

                        if (styleName && typeof styleName === "string") {
                            if (this._allStyles.hasOwnProperty(styleName)) {
                                this._allStyles[styleName].parse(customStyle["style"]);
                            }
                            else {
                                this._allStyles[styleName] = new ContainerStyleDefinition(customStyle["style"]);
                            }
                        }
                    }
                }
            }
        }
    }

    toJSON() {
        let customStyleArray: any[] = [];

        Object.keys(this._allStyles).forEach(
            (key) => {
                if (!this._allStyles[key].isBuiltIn) {
                    customStyleArray.push({
                        name: key,
                        style: this._allStyles[key]
                    });
                }
            });

        let result: any = {
            default: this.default,
            emphasis: this.emphasis
        }

        if (customStyleArray.length > 0) {
            result.customStyles = customStyleArray;
        }

        return result;
    }

    getStyleByName(name: string | undefined, defaultValue?: ContainerStyleDefinition): ContainerStyleDefinition {
        if (name && this._allStyles.hasOwnProperty(name)) {
            return this._allStyles[name];
        }
        else {
            return defaultValue ? defaultValue : this._allStyles[Enums.ContainerStyle.Default];
        }
    }

    get default(): ContainerStyleDefinition {
        return this._allStyles[Enums.ContainerStyle.Default];
    }

    get emphasis(): ContainerStyleDefinition {
        return this._allStyles[Enums.ContainerStyle.Emphasis];
    }
}

export interface IFontSizeDefinitions {
    small: number;
    default: number;
    medium: number;
    large: number;
    extraLarge: number;
}

export interface IFontWeightDefinitions {
    lighter: number;
    default: number;
    bolder: number;
}

export class FontTypeDefinition {
    static readonly monospace = new FontTypeDefinition("'Courier New', Courier, monospace");

    fontFamily?: string = "Segoe UI,Segoe,Segoe WP,Helvetica Neue,Helvetica,sans-serif";

    fontSizes: IFontSizeDefinitions = {
        small: 12,
        default: 14,
        medium: 17,
        large: 21,
        extraLarge: 26
    };

    fontWeights: IFontWeightDefinitions = {
        lighter: 200,
        default: 400,
        bolder: 600
    };

    constructor(fontFamily?: string) {
        if (fontFamily) {
            this.fontFamily = fontFamily;
        }
    }

    parse(obj?: any) {
        this.fontFamily = obj["fontFamily"] || this.fontFamily;
        this.fontSizes = {
            small: obj.fontSizes && obj.fontSizes["small"] || this.fontSizes.small,
            default: obj.fontSizes && obj.fontSizes["default"] || this.fontSizes.default,
            medium: obj.fontSizes && obj.fontSizes["medium"] || this.fontSizes.medium,
            large: obj.fontSizes && obj.fontSizes["large"] || this.fontSizes.large,
            extraLarge: obj.fontSizes && obj.fontSizes["extraLarge"] || this.fontSizes.extraLarge
        };
        this.fontWeights = {
            lighter: obj.fontWeights && obj.fontWeights["lighter"] || this.fontWeights.lighter,
            default: obj.fontWeights && obj.fontWeights["default"] || this.fontWeights.default,
            bolder: obj.fontWeights && obj.fontWeights["bolder"] || this.fontWeights.bolder
        };
    }
}

export class FontTypeSet {
    default: FontTypeDefinition;
    monospace: FontTypeDefinition;

    constructor(obj?: any) {
        this.default = new FontTypeDefinition();
        this.monospace = new FontTypeDefinition("'Courier New', Courier, monospace");

        if (obj) {
            this.default.parse(obj["default"]);
            this.monospace.parse(obj["monospace"]);
        }
    }

    getStyleDefinition(style: Enums.FontType | undefined): FontTypeDefinition {
        switch (style) {
            case Enums.FontType.Monospace:
                return this.monospace;
            case Enums.FontType.Default:
            default:
                return this.default;
        }
    }
}

export class HostConfig {
    readonly hostCapabilities = new HostCapabilities();

    private _legacyFontType: FontTypeDefinition;

    choiceSetInputValueSeparator: string = ",";
    supportsInteractivity: boolean = true;
    lineHeights?: ILineHeightDefinitions;
    fontTypes?: FontTypeSet;

    readonly spacing = {
        small: 3,
        default: 8,
        medium: 20,
        large: 30,
        extraLarge: 40,
        padding: 15
    };

    readonly separator = {
        lineThickness: 1,
        lineColor: "#EEEEEE"
    };

    readonly imageSizes = {
        small: 40,
        medium: 80,
        large: 160
    };

    readonly containerStyles: ContainerStyleSet = new ContainerStyleSet();
    readonly inputs: InputConfig = new InputConfig();
    readonly actions: ActionsConfig = new ActionsConfig();
    readonly adaptiveCard: AdaptiveCardConfig = new AdaptiveCardConfig();
    readonly imageSet: ImageSetConfig = new ImageSetConfig();
    readonly media: MediaConfig = new MediaConfig();
    readonly factSet: FactSetConfig = new FactSetConfig();

    cssClassNamePrefix?: string;
    alwaysAllowBleed: boolean = false;

    constructor(obj?: any) {
        if (obj) {
            if (typeof obj === "string" || obj instanceof String) {
                obj = JSON.parse(obj as string);
            }

            this.choiceSetInputValueSeparator = (obj && typeof obj["choiceSetInputValueSeparator"] === "string") ? obj["choiceSetInputValueSeparator"] : this.choiceSetInputValueSeparator;
            this.supportsInteractivity = (obj && typeof obj["supportsInteractivity"] === "boolean") ? obj["supportsInteractivity"] : this.supportsInteractivity;

            this._legacyFontType = new FontTypeDefinition();
            this._legacyFontType.parse(obj);

            if (obj.fontTypes) {
                this.fontTypes = new FontTypeSet(obj.fontTypes);
            }

            if (obj.lineHeights) {
                this.lineHeights = {
                    small: obj.lineHeights["small"],
                    default: obj.lineHeights["default"],
                    medium: obj.lineHeights["medium"],
                    large: obj.lineHeights["large"],
                    extraLarge: obj.lineHeights["extraLarge"]
                };
            };

            this.imageSizes = {
                small: obj.imageSizes && obj.imageSizes["small"] || this.imageSizes.small,
                medium: obj.imageSizes && obj.imageSizes["medium"] || this.imageSizes.medium,
                large: obj.imageSizes && obj.imageSizes["large"] || this.imageSizes.large,
            };

            this.containerStyles = new ContainerStyleSet(obj["containerStyles"]);
            this.spacing = {
                small: obj.spacing && obj.spacing["small"] || this.spacing.small,
                default: obj.spacing && obj.spacing["default"] || this.spacing.default,
                medium: obj.spacing && obj.spacing["medium"] || this.spacing.medium,
                large: obj.spacing && obj.spacing["large"] || this.spacing.large,
                extraLarge: obj.spacing && obj.spacing["extraLarge"] || this.spacing.extraLarge,
                padding: obj.spacing && obj.spacing["padding"] || this.spacing.padding
            };

            this.separator = {
                lineThickness: obj.separator && obj.separator["lineThickness"] || this.separator.lineThickness,
                lineColor: obj.separator && obj.separator["lineColor"] || this.separator.lineColor
            }

            this.inputs = new InputConfig(obj.inputs || this.inputs);
            this.actions = new ActionsConfig(obj.actions || this.actions);
            this.adaptiveCard = new AdaptiveCardConfig(obj.adaptiveCard || this.adaptiveCard);
            this.imageSet = new ImageSetConfig(obj["imageSet"]);
            this.factSet = new FactSetConfig(obj["factSet"])
        }
    }

    getFontTypeDefinition(style?: Enums.FontType): FontTypeDefinition {
        if (this.fontTypes) {
            return this.fontTypes.getStyleDefinition(style);
        }
        else {
            return style == Enums.FontType.Monospace ? FontTypeDefinition.monospace : this._legacyFontType;
        }
    }

    getEffectiveSpacing(spacing: Enums.Spacing): number {
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
    }

    paddingDefinitionToSpacingDefinition(paddingDefinition: Shared.PaddingDefinition): Shared.SpacingDefinition {
        return new Shared.SpacingDefinition(
            this.getEffectiveSpacing(paddingDefinition.top),
            this.getEffectiveSpacing(paddingDefinition.right),
            this.getEffectiveSpacing(paddingDefinition.bottom),
            this.getEffectiveSpacing(paddingDefinition.left));
    }

    makeCssClassNames(...classNames: string[]): string[] {
        let result: string[] = [];

        for (let className of classNames) {
            result.push((this.cssClassNamePrefix ? this.cssClassNamePrefix + "-" : "") + className);
        }

        return result;
    }

    makeCssClassName(...classNames: string[]): string {
        let result = this.makeCssClassNames(...classNames).join(" ");

        return result ? result : "";
    }

    get fontFamily(): string | undefined {
        return this._legacyFontType.fontFamily;
    }

    set fontFamily(value: string | undefined) {
        this._legacyFontType.fontFamily = value;
    }

    get fontSizes(): IFontSizeDefinitions {
        return this._legacyFontType.fontSizes;
    }

    get fontWeights(): IFontWeightDefinitions {
        return this._legacyFontType.fontWeights;
    }
}

export const defaultHostConfig: HostConfig = new HostConfig(
    {
        supportsInteractivity: true,
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
        fontTypes: {
            default: {
                fontFamily: "'Segoe UI', Tahoma, Geneva, Verdana, sans-serif",
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
                }
            },
            monospace: {
                fontFamily: "'Courier New', Courier, monospace",
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
                }
            }
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
                    dark: {
                        default: "#000000",
                        subtle: "#66000000"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#33000000"
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
                        default: "#028A02",
                        subtle: "#DD027502"
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
                    dark: {
                        default: "#000000",
                        subtle: "#66000000"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#33000000"
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
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            },
            accent: {
                backgroundColor: "#C7DEF9",
                foregroundColors: {
                    default: {
                        default: "#333333",
                        subtle: "#EE333333"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#66000000"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#33000000"
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
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            },
            good: {
                backgroundColor: "#CCFFCC",
                foregroundColors: {
                    default: {
                        default: "#333333",
                        subtle: "#EE333333"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#66000000"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#33000000"
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
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            },
            attention: {
                backgroundColor: "#FFC5B2",
                foregroundColors: {
                    default: {
                        default: "#333333",
                        subtle: "#EE333333"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#66000000"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#33000000"
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
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            },
            warning: {
                backgroundColor: "#FFE2B2",
                foregroundColors: {
                    default: {
                        default: "#333333",
                        subtle: "#EE333333"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#66000000"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#33000000"
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
                        default: "#028A02",
                        subtle: "#DD027502"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            }
        },
        inputs: {
            label: {
                requiredInputs: {
                    color: Enums.TextColor.Accent,
                    size: Enums.TextSize.ExtraLarge,
                    weight: Enums.TextWeight.Bolder,
                    isSubtle: true,
                    suffix: " (required)",
                    suffixColor: Enums.TextColor.Good
                },
                optionalInputs: {
                    color: Enums.TextColor.Warning,
                    size: Enums.TextSize.Medium,
                    weight: Enums.TextWeight.Lighter,
                    isSubtle: false
                }
            },
            errorMessage: {
                color: Enums.TextColor.Accent,
                size: Enums.TextSize.Small,
                weight: Enums.TextWeight.Bolder
            }
        },
        actions: {
            maxActions: 5,
            spacing: Enums.Spacing.Default,
            buttonSpacing: 10,
            showCard: {
                actionMode: Enums.ShowCardActionMode.Inline,
                inlineTopMargin: 16
            },
            actionsOrientation: Enums.Orientation.Horizontal,
            actionAlignment: Enums.ActionAlignment.Left
        },
        adaptiveCard: {
            allowCustomStyle: false
        },
        imageSet: {
            imageSize: Enums.Size.Medium,
            maxImageHeight: 100
        },
        factSet: {
            title: {
                color: Enums.TextColor.Default,
                size: Enums.TextSize.Default,
                isSubtle: false,
                weight: Enums.TextWeight.Bolder,
                wrap: true,
                maxWidth: 150,
            },
            value: {
                color: Enums.TextColor.Default,
                size: Enums.TextSize.Default,
                isSubtle: false,
                weight: Enums.TextWeight.Default,
                wrap: true,
            },
            spacing: 10
        }
    });
