// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";
import * as Utils from "./utils";
import * as Shared from "./shared";

export interface IValidationError {
    error: Enums.ValidationError,
    message: string;
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
            this.maxImageHeight = Utils.getNumberValue(obj["maxImageHeight"], 100);
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
    defaultPoster: string;
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

export class FactTextDefinition {
    size: Enums.TextSize = Enums.TextSize.Default;
    color: Enums.TextColor = Enums.TextColor.Default;;
    isSubtle: boolean = false;
    weight: Enums.TextWeight = Enums.TextWeight.Default;
    wrap: boolean = true;

    constructor(obj?: any) {
        if (obj) {
            this.size = Utils.parseHostConfigEnum(Enums.TextSize, obj["size"], Enums.TextSize.Default);
            this.color = Utils.parseHostConfigEnum(Enums.TextColor, obj["color"], Enums.TextColor.Default);
            this.isSubtle = obj["isSubtle"] || this.isSubtle;
            this.weight = Utils.parseHostConfigEnum(Enums.TextWeight, obj["weight"], this.getDefaultWeight());
            this.wrap = obj["wrap"] != null ? obj["wrap"] : this.wrap;
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
            weight: Enums.TextWeight[this.weight],
            wrap: this.wrap
        }
    }
}

export class FactTitleDefinition extends FactTextDefinition {
    maxWidth?: number = 150;
    weight: Enums.TextWeight = Enums.TextWeight.Bolder;

    constructor(obj?: any) {
        super(obj);

        if (obj) {
            this.maxWidth = obj["maxWidth"] != null ? obj["maxWidth"] : this.maxWidth;
			this.weight = Utils.parseHostConfigEnum(Enums.TextWeight, obj["weight"], Enums.TextWeight.Bolder);
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
            this.actionMode = Utils.parseHostConfigEnum(Enums.ShowCardActionMode, obj["actionMode"], Enums.ShowCardActionMode.Inline);
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
    iconSize: number = 24;

    constructor(obj?: any) {
        if (obj) {
            this.maxActions = obj["maxActions"] != null ? obj["maxActions"] : this.maxActions;
            this.spacing = Utils.parseHostConfigEnum(Enums.Spacing, obj.spacing && obj.spacing, Enums.Spacing.Default);
            this.buttonSpacing = obj["buttonSpacing"] != null ? obj["buttonSpacing"] : this.buttonSpacing;
            this.showCard = new ShowCardActionConfig(obj["showCard"]);
            this.preExpandSingleShowCardAction = Utils.getBoolValue(obj["preExpandSingleShowCardAction"], false);
            this.actionsOrientation = Utils.parseHostConfigEnum(Enums.Orientation, obj["actionsOrientation"], Enums.Orientation.Horizontal);
            this.actionAlignment = Utils.parseHostConfigEnum(Enums.ActionAlignment, obj["actionAlignment"], Enums.ActionAlignment.Left);
            this.iconPlacement = Utils.parseHostConfigEnum(Enums.ActionIconPlacement, obj["iconPlacement"], Enums.ActionIconPlacement.LeftOfTitle);
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
            (this[propertyName] as TextColorDefinition).parse(obj[propertyName]);
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
            "good": { default: "#54A254", subtle: "#DD54A254" },
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
    private _allStyles: object = {};

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
                for (var customStyle of customStyleArray) {
                    if (customStyle) {
                        var styleName = customStyle["name"];

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
        var customStyleArray: Array<any> = [];

        Object.keys(this._allStyles).forEach(
            (key) => {
                if (!this._allStyles[key].isBuiltIn) {
                    customStyleArray.push({
                        name: key,
                        style: this._allStyles[key]
                    });
                }
            });

        var result: any = {
            default: this.default,
            emphasis: this.emphasis
        }

        if (customStyleArray.length > 0) {
            result.customStyles = customStyleArray;
        }

        return result;
    }

    getStyleByName(name: string, defaultValue: ContainerStyleDefinition = null): ContainerStyleDefinition {
        return this._allStyles.hasOwnProperty(name) ? this._allStyles[name] : defaultValue;
    }

    get default(): ContainerStyleDefinition {
        return this._allStyles[Enums.ContainerStyle.Default];
    }

    get emphasis(): ContainerStyleDefinition {
        return this._allStyles[Enums.ContainerStyle.Emphasis];
    }
}

export class Version {
    private _versionString: string;
    private _major: number;
    private _minor: number;
    private _isValid: boolean = true;
    private _label: string;

    constructor(major: number = 1, minor: number = 1, label?: string) {
        this._major = major;
        this._minor = minor;
        this._label = label;
    }

    static parse(versionString: string, errors?: Array<IValidationError>): Version {
        if (!versionString) {
            return null;
        }

        var result = new Version();
        result._versionString = versionString;

        var regEx = /(\d+).(\d+)/gi;
        var matches = regEx.exec(versionString);

        if (matches != null && matches.length == 3) {
            result._major = parseInt(matches[1]);
            result._minor = parseInt(matches[2]);
        }
        else {
            result._isValid = false;
        }

        if (!result._isValid && errors) {
            errors.push(
                {
                    error: Enums.ValidationError.InvalidPropertyValue,
                    message: "Invalid version string: " + result._versionString
                }
            );
        }

        return result;
    }

    toString(): string {
        return !this._isValid ? this._versionString : this._major + "." + this._minor;
    }

    compareTo(otherVersion: Version): number {
        if (!this.isValid || !otherVersion.isValid) {
            throw new Error("Cannot compare invalid version.");
        }

        if (this.major > otherVersion.major) {
            return 1;
        }
        else if (this.major < otherVersion.major) {
            return -1;
        }
        else if (this.minor > otherVersion.minor) {
            return 1;
        }
        else if (this.minor < otherVersion.minor) {
            return -1;
        }

        return 0;
    }

    get label(): string {
        return this._label ? this._label : this.toString();
    }

    get major(): number {
        return this._major;
    }

    get minor(): number {
        return this._minor;
    }

    get isValid(): boolean {
        return this._isValid;
    }
}

export type HostCapabilityVersion = Version | "*";
export type HostCapabilityMap = { [key: string]: HostCapabilityVersion };

export class HostCapabilities {
    private setCapability(name: string, version: HostCapabilityVersion) {
        if (!this.capabilities) {
            this.capabilities = { };
        }

        this.capabilities[name] = version;
    }

    capabilities: HostCapabilityMap = null;

    parse(json: any, errors?: Array<IValidationError>) {
        if (json) {
            for (let name in json) {
                let jsonVersion = json[name];

                if (typeof jsonVersion === "string") {
                    if (jsonVersion == "*") {
                        this.setCapability(name, "*");
                    }
                    else {
                        let version = Version.parse(jsonVersion, errors);

                        if (version.isValid) {
                            this.setCapability(name, version);
                        }
                    }
                }
            }
        }
    }

    hasCapability(name: string, version: HostCapabilityVersion): boolean {
        if (this.capabilities && this.capabilities.hasOwnProperty(name)) {
            if (version == "*" || this.capabilities[name] == "*") {
                return true;
            }

            return version.compareTo(<Version>this.capabilities[name]) <= 0;
        }

        return false;
    }

    areAllMet(hostCapabilities: HostCapabilities): boolean {
        if (this.capabilities) {
            for (let capabilityName in this.capabilities) {
                if (!hostCapabilities.hasCapability(capabilityName, this.capabilities[capabilityName])) {
                    return false;
                }
            }
        }

        return true;
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
    static readonly monospace =  new FontTypeDefinition("'Courier New', Courier, monospace");

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

    getStyleDefinition(style: Enums.FontType): FontTypeDefinition {
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
    fontTypes: FontTypeSet = null;

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
    readonly actions: ActionsConfig = new ActionsConfig();
    readonly adaptiveCard: AdaptiveCardConfig = new AdaptiveCardConfig();
    readonly imageSet: ImageSetConfig = new ImageSetConfig();
    readonly media: MediaConfig = new MediaConfig();
    readonly factSet: FactSetConfig = new FactSetConfig();

    cssClassNamePrefix: string = null;
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

    get fontFamily(): string {
        return this._legacyFontType.fontFamily;
    }

    set fontFamily(value: string) {
        this._legacyFontType.fontFamily = value;
    }

    get fontSizes(): IFontSizeDefinitions {
        return this._legacyFontType.fontSizes;
    }

    get fontWeights(): IFontWeightDefinitions {
        return this._legacyFontType.fontWeights;
    }
}
