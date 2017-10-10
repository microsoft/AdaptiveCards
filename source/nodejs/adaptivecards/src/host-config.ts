import * as Enums from "./enums";
import * as Utils from "./utils";

export class SpacingDefinition {
    left: number = 0;
    top: number = 0;
    right: number = 0;
    bottom: number = 0;

    constructor(obj?: any) {
        if (obj) {
            this.top = obj["top"] || this.top;
            this.right = obj["right"] || this.right;
            this.bottom = obj["bottom"] || this.bottom;
            this.left = obj["left"] || this.left;
        }
    }
}

export class PaddingDefinition {
    top: Enums.Padding = Enums.Padding.None;
    right: Enums.Padding = Enums.Padding.None;
    bottom: Enums.Padding = Enums.Padding.None;
    left: Enums.Padding = Enums.Padding.None;

    constructor(obj?: any) {
        if (obj) {
            this.top = Utils.parseHostConfigEnum(Enums.Padding, obj["top"], Enums.Padding.None);
            this.right = Utils.parseHostConfigEnum(Enums.Padding, obj["right"], Enums.Padding.None);
            this.bottom = Utils.parseHostConfigEnum(Enums.Padding, obj["bottom"], Enums.Padding.None);
            this.left = Utils.parseHostConfigEnum(Enums.Padding, obj["left"], Enums.Padding.None);
        }
    }

    toJSON() {
        return {
            top: Enums.Padding[this.top],
            right: Enums.Padding[this.right],
            bottom: Enums.Padding[this.bottom],
            left: Enums.Padding[this.left],
        }
    }
}

export class TextColorDefinition {
    normal: string = "#0000FF";
    subtle: string = "#222222";

    constructor(obj?: any) {
        if (obj) {
            this.normal = obj["normal"] || this.normal;
            this.subtle = obj["subtle"] || this.subtle;
        }
    }
}

export class ContainerStyleDefinition {
    backgroundColor?: string;
    readonly fontColors = {
        default: new TextColorDefinition(),
        accent: new TextColorDefinition(),
        good: new TextColorDefinition(),
        warning: new TextColorDefinition(),
        attention: new TextColorDefinition()
    };

    constructor(obj?: any) {
        if (obj) {
            this.backgroundColor = obj["backgroundColor"];
            this.fontColors = {
                default: new TextColorDefinition(obj["fontColors"]["default"]),
                accent: new TextColorDefinition(obj["fontColors"]["accent"]),
                good: new TextColorDefinition(obj["fontColors"]["good"]),
                warning: new TextColorDefinition(obj["fontColors"]["warning"]),
                attention: new TextColorDefinition(obj["fontColors"]["attention"])
            }
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

export class ImageConfig {
    size: Enums.Size = Enums.Size.Medium;

    constructor(obj?: any) {
        if (obj) {
            this.size = obj["size"] || this.size;
        }
    }

    toJSON() {
        return {
            size: Enums.Size[this.size]
        }
    }
}

export class ImageSetConfig {
    imageSize: Enums.Size = Enums.Size.Medium;
    maxImageHeight: number = 100;

    constructor(obj?: any) {
        if (obj) {
            this.imageSize = obj["imageSize"] || this.imageSize;
            this.maxImageHeight = Utils.getValueOrDefault<number>("maxImageHeight", 100);
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
            this.weight = Utils.parseHostConfigEnum(Enums.TextWeight, obj["weight"], Enums.TextWeight.Default);
            this.wrap = obj["wrap"] || this.wrap;
        }
    }

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

export class FactTitleDefinition extends FactTextDefinition {
    maxWidth?: number = 150;
    weight: Enums.TextWeight = Enums.TextWeight.Bolder;

    constructor(obj?: any) {
        super(obj);

        if (obj) {
            this.maxWidth = obj["maxWidth"] || this.maxWidth;
        }
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
            this.spacing = obj["spacing"] || this.spacing;
        }
    }
}

export class ShowCardActionConfig {
    actionMode: Enums.ShowCardActionMode = Enums.ShowCardActionMode.Inline;
    inlineTopMargin: number = 16;
    style?: Enums.ContainerStyle = Enums.ContainerStyle.Emphasis;

    constructor(obj?: any) {
        if (obj) {
            this.actionMode = Utils.parseHostConfigEnum(Enums.ShowCardActionMode, obj["actionMode"], Enums.ShowCardActionMode.Inline);
            this.inlineTopMargin = obj["inlineTopMargin"] || this.inlineTopMargin;
            this.style = Utils.parseHostConfigEnum(Enums.ContainerStyle, obj["style"], Enums.ContainerStyle.Emphasis);
        }
    }

    toJSON() {
        return {
            actionMode: Enums.ShowCardActionMode[this.actionMode],
            inlineTopMargin: this.inlineTopMargin,
            style: Enums.ContainerStyle[this.style]
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
            this.maxActions = obj["maxActions"] || this.maxActions;
            this.spacing = Utils.parseHostConfigEnum(Enums.Spacing, obj["spacing"], Enums.Spacing.Default);
            this.buttonSpacing = obj["buttonSpacing"] || this.buttonSpacing;
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

export class ContainerStyleSet {
    readonly default: ContainerStyleDefinition = new ContainerStyleDefinition();
    readonly emphasis: ContainerStyleDefinition = new ContainerStyleDefinition();

    constructor(obj?: any) {
        this.emphasis.backgroundColor = "#EEEEEE";
        if (obj) {
            this.default = new ContainerStyleDefinition(obj["default"]);
            this.emphasis = new ContainerStyleDefinition(obj["emphasis"])
        }
    }
}

export class HostConfig {
    supportsInteractivity: boolean = true;
    fontFamily?: string = "Segoe UI";
    readonly fontSizes = {
        small: 8,
        default: 10,
        medium: 12,
        large: 14,
        extraLarge: 16
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
    readonly spacing = {
        small: 3,
        default: 8,
        medium: 20,
        large: 30,
        extraLarge: 40,
        padding: 20
    };
    readonly separator = {
        lineThickness: 1,
        lineColor: "#EEEEEE"
    }
    readonly actions: ActionsConfig = new ActionsConfig();
    readonly adaptiveCard: AdaptiveCardConfig = new AdaptiveCardConfig();
    readonly image: ImageConfig = new ImageConfig();
    readonly imageSet: ImageSetConfig = new ImageSetConfig();
    readonly factSet: FactSetConfig = new FactSetConfig();

    constructor(obj?: any) {
        if (obj) {
            if (typeof obj === "string" || obj instanceof String) {
                obj = JSON.parse(obj as string);
            }

            this.supportsInteractivity = obj["supportsInteractivity"] || this.supportsInteractivity;
            this.fontFamily = obj["fontFamily"] || this.fontFamily;
            this.fontSizes = {
                small: obj["fontSizes"]["small"] || this.fontSizes.small,
                default: obj["fontSizes"]["default"] || this.fontSizes.default,
                medium: obj["fontSizes"]["medium"] || this.fontSizes.medium,
                large: obj["fontSizes"]["large"] || this.fontSizes.large,
                extraLarge: obj["fontSizes"]["extraLarge"] || this.fontSizes.extraLarge
            };

            this.fontWeights = {
                lighter: obj["fontWeights"]["lighter"] || this.fontWeights.lighter,
                default: obj["fontWeights"]["default"] || this.fontWeights.default,
                bolder: obj["fontWeights"]["bolder"] || this.fontWeights.bolder
            };

            this.imageSizes = {
                small: obj["imageSizes"]["small"] || this.imageSizes.small,
                medium: obj["imageSizes"]["medium"] || this.imageSizes.medium,
                large: obj["imageSizes"]["large"] || this.imageSizes.large,
            };

            this.containerStyles = new ContainerStyleSet(obj["containerStyles"]);
            this.spacing = {
                small: obj["spacing"]["small"] || this.spacing.small,
                default: obj["spacing"]["default"] || this.spacing.default,
                medium: obj["spacing"]["medium"] || this.spacing.medium,
                large: obj["spacing"]["large"] || this.spacing.large,
                extraLarge: obj["spacing"]["extraLarge"] || this.spacing.extraLarge,
                padding: obj["spacing"]["padding"] || this.spacing.padding
            };

            this.separator = {
                lineThickness: obj["separator"]["lineThickness"] || this.separator.lineThickness,
                lineColor: obj["separator"]["lineColor"] || this.separator.lineColor
            }

            this.actions = new ActionsConfig(obj["actions"]);
            this.adaptiveCard = new AdaptiveCardConfig(obj["adaptiveCard"]);
            this.image = new ImageConfig(obj["image"]);
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

    getEffectivePadding(padding: Enums.Padding): number {
        switch (padding) {
            case Enums.Padding.Default:
                return this.spacing.padding;
            default:
                return 0;
        }
    }

    paddingToSpacingDefinition(padding: PaddingDefinition): SpacingDefinition {
        return new SpacingDefinition({
            top: this.getEffectivePadding(padding.top),
            right: this.getEffectivePadding(padding.right),
            bottom: this.getEffectivePadding(padding.bottom),
            left: this.getEffectivePadding(padding.left)
        })
    }

    getContainerStyleDefinition(containerStyle: Enums.ContainerStyle) {
        switch (containerStyle) {
            case Enums.ContainerStyle.Emphasis:
                return this.containerStyles.emphasis;
            default:
                return this.containerStyles.default;
        }
    }
}