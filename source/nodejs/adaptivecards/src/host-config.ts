import * as Enums from "./enums";
import * as Utils from "./utils";
import { TextColor } from "./adaptivecards";

export class TextColorDefinition {
    default: string = "#000000";
    subtle: string = "#666666";

    constructor(obj?: any) {
        if (obj) {
            this.default = obj["default"] || this.default;
            this.subtle = obj["subtle"] || this.subtle;
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
            this.maxImageHeight = Utils.getValueOrDefault<number>(obj["maxImageHeight"], 100);
        }
    }

    toJSON() {
        return {
            imageSize: Enums.Size[this.imageSize],
            maxImageHeight: this.maxImageHeight
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

    constructor(obj?: any) {
        if (obj) {
            this.maxActions = obj["maxActions"] != null ? obj["maxActions"] : this.maxActions;
            this.spacing = Utils.parseHostConfigEnum(Enums.Spacing, obj.spacing && obj.spacing, Enums.Spacing.Default);
            this.buttonSpacing = obj["buttonSpacing"] != null ? obj["buttonSpacing"] : this.buttonSpacing;
            this.showCard = new ShowCardActionConfig(obj["showCard"]);
            this.preExpandSingleShowCardAction = Utils.getValueOrDefault<boolean>(obj["preExpandSingleShowCardAction"], false);
            this.actionsOrientation = Utils.parseHostConfigEnum(Enums.Orientation, obj["actionsOrientation"], Enums.Orientation.Horizontal);
            this.actionAlignment = Utils.parseHostConfigEnum(Enums.ActionAlignment, obj["actionAlignment"], Enums.ActionAlignment.Left);
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

export class ContainerStyleDefinition {
    private getTextColorDefinitionOrDefault(obj: any, defaultValue: { default: string, subtle: string }) {
        return new TextColorDefinition(obj ? obj : defaultValue);
    }

    backgroundColor?: string;

    readonly foregroundColors = {
        default: new TextColorDefinition(),
        dark: new TextColorDefinition(),
        light: new TextColorDefinition(),
        accent: new TextColorDefinition(),
        good: new TextColorDefinition(),
        warning: new TextColorDefinition(),
        attention: new TextColorDefinition()
    };

    parse(obj: any) {
        if (obj) {
            this.backgroundColor = obj["backgroundColor"];

            if (obj.foregroundColors) {
                this.foregroundColors.default = this.getTextColorDefinitionOrDefault(obj.foregroundColors["default"], { default: "#333333", subtle: "#EE333333" });
                this.foregroundColors.dark = this.getTextColorDefinitionOrDefault(obj.foregroundColors["dark"], { default: "#000000", subtle: "#66000000" });
                this.foregroundColors.light = this.getTextColorDefinitionOrDefault(obj.foregroundColors["light"], { default: "#FFFFFF", subtle: "#33000000" });
                this.foregroundColors.accent = this.getTextColorDefinitionOrDefault(obj.foregroundColors["accent"], { default: "#2E89FC", subtle: "#882E89FC" });
                this.foregroundColors.good = this.getTextColorDefinitionOrDefault(obj.foregroundColors["good"], { default: "#54A254", subtle: "#DD54A254" });
                this.foregroundColors.warning = this.getTextColorDefinitionOrDefault(obj.foregroundColors["warning"], { default: "#E69500", subtle: "#DDE69500" });
                this.foregroundColors.attention = this.getTextColorDefinitionOrDefault(obj.foregroundColors["attention"], { default: "#CC3300", subtle: "#DDCC3300" });
            }
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

export class ContainerStyleSet {
    private _allStyles: object = {};

    constructor(obj?: any) {
        this._allStyles[Enums.ContainerStyle.Default] = new BuiltInContainerStyleDefinition();
        this._allStyles[Enums.ContainerStyle.Emphasis] = new BuiltInContainerStyleDefinition();

        if (obj) {
            this._allStyles[Enums.ContainerStyle.Default].parse(obj[Enums.ContainerStyle.Default]);
            this._allStyles[Enums.ContainerStyle.Emphasis].parse(obj[Enums.ContainerStyle.Emphasis]);

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

export class HostConfig {
    choiceSetInputValueSeparator: string = ",";
    supportsInteractivity: boolean = true;

    fontFamily?: string = "Segoe UI,Segoe,Segoe WP,Helvetica Neue,Helvetica,sans-serif";
    
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

    readonly fontSizes = {
        small: 12,
        default: 14,
        medium: 17,
        large: 21,
        extraLarge: 26
    };
    readonly fontWeights = {
        lighter: 200,
        default: 400,
        bolder: 600
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
    readonly factSet: FactSetConfig = new FactSetConfig();

    constructor(obj?: any) {
        if (obj) {
            if (typeof obj === "string" || obj instanceof String) {
                obj = JSON.parse(obj as string);
            }

            this.choiceSetInputValueSeparator = (obj && typeof obj["choiceSetInputValueSeparator"] === "string") ? obj["choiceSetInputValueSeparator"] : this.choiceSetInputValueSeparator;
            this.supportsInteractivity = (obj && typeof obj["supportsInteractivity"] === "boolean") ? obj["supportsInteractivity"] : this.supportsInteractivity;
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
}
