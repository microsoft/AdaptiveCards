export enum Size {
    Auto,
    Stretch,
    Small,
    Medium,
    Large
}

export enum TextSize {
    Small,
    Normal,
    Medium,
    Large,
    ExtraLarge
}

export enum TextWeight {
    Lighter,
    Normal,
    Bolder
}

export enum TextColor {
    Dark,
    Light,
    Accent,
    Good,
    Warning,
    Attention
}

export enum HorizontalAlignment {
    Left,
    Center,
    Right
}

export enum ContainerStyle {
    Normal,
    Emphasis
}

export enum ImageStyle {
    Normal,
    Person
}

export enum Separation  {
    None,
    Default,
    Strong
}

export enum ValidationError {
    ActionTypeNotAllowed,
    CollectionCantBeEmpty,
    ElementTypeNotAllowed,
    InteractivityNotAllowed,
    MissingCardType,
    PropertyCantBeNull,
    TooManyActions,
    UnknownActionType,
    UnknownElementType,
    UnsupportedCardVersion
}

export enum ShowCardActionMode {
    Inline,
    InlineEdgeToEdge,
    Popup
}

export enum Orientation {
    Horizontal,
    Vertical
}

export function stringToSize(value: string, defaultValue: Size): Size {
    switch (value) {
        case "auto":
            return Size.Auto;
        case "stretch":
            return Size.Stretch;
        case "small":
            return Size.Small;
        case "medium":
            return Size.Medium;
        case "large":
            return Size.Large;
        default:
            return defaultValue;
    }
}

export function stringToTextSize(value: string, defaultValue: TextSize): TextSize {
    switch (value) {
        case "small":
            return TextSize.Small;
        case "normal":
            return TextSize.Normal;
        case "medium":
            return TextSize.Medium;
        case "large":
            return TextSize.Large;
        case "extraLarge":
            return TextSize.ExtraLarge;
        default:
            return defaultValue;
    }
}

export function stringToTextWeight(value: string, defaultValue: TextWeight): TextWeight {
    switch (value) {
        case "lighter":
            return TextWeight.Lighter;
        case "normal":
            return TextWeight.Normal;
        case "bolder":
            return TextWeight.Bolder;
        default:
            return defaultValue;
    }
}

export function stringToTextColor(value: string, defaultValue: TextColor): TextColor {
    switch (value) {
        case "dark":
            return TextColor.Dark;
        case "light":
            return TextColor.Light;
        case "accent":
            return TextColor.Accent;
        case "good":
            return TextColor.Good;
        case "warning":
            return TextColor.Warning;
        case "attention":
            return TextColor.Attention;
        default:
            return defaultValue;
    }
}

export function stringToHorizontalAlignment(value: string, defaultValue: HorizontalAlignment): HorizontalAlignment {
    switch (value) {
        case "left":
            return HorizontalAlignment.Left;
        case "center":
            return HorizontalAlignment.Center;
        case "right":
            return HorizontalAlignment.Right;
        default:
            return defaultValue;
    }
}

export function stringToImageStyle(value: string, defaultValue: ImageStyle): ImageStyle {
    switch (value) {
        case "person":
            return ImageStyle.Person;
        case "normal":
            return ImageStyle.Normal;
        default:
            return defaultValue;
    }
}

export function stringToContainerStyle(value: string, defaultValue: ContainerStyle): ContainerStyle {
    switch (value) {
        case "normal":
            return ContainerStyle.Normal;
        case "emphasis":
            return ContainerStyle.Emphasis;
        default:
            return defaultValue;
    }
}

export function stringToOrientation(value: string, defaultValue: Orientation): Orientation {
    switch (value) {
        case "horizontal":
            return Orientation.Horizontal;
        case "vertical":
            return Orientation.Vertical;
        default:
            return defaultValue;
    }
}

export function stringToSeparation(value: string, defaultValue: Separation): Separation {
    switch (value) {
        case "none":
            return Separation.None;
        case "default":
            return Separation.Default;
        case "strong":
            return Separation.Strong;
        default:
            return defaultValue;
    }
}