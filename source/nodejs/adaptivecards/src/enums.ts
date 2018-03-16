export enum Size {
    Auto,
    Stretch,
    Small,
    Medium,
    Large
}

export enum TextSize {
    Small,
    Default,
    Medium,
    Large,
    ExtraLarge
}

export enum Spacing {
    None,
    Small,
    Default,
    Medium,
    Large,
    ExtraLarge,
    Padding
}

export enum TextWeight {
    Lighter,
    Default,
    Bolder
}

export enum TextColor {
    Default,
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

export enum VerticalAlignment {
    Top,
    Center,
    Bottom
}

export enum ActionAlignment {
    Left,
    Center,
    Right,
    Stretch
}

export enum ImageStyle {
    Default,
    Person
}

export enum ShowCardActionMode {
    Inline,
    Popup
}

export enum Orientation {
    Horizontal,
    Vertical
}

export enum BackgroundImageMode {
    Stretch,
    RepeatHorizontally,
    RepeatVertically,
    Repeat
}

/*
    This should really be a string enum, e.g.
    
        export enum ContainerStyle {
            Default = "default",
            Emphasis = "emphasis"
        }

    However, some hosts do not use a version of TypeScript
    recent enough to understand string enums. This is
    a compatible construct that does not require using
    a more recent version of TypeScript.
*/
export class ContainerStyle {
    static readonly Default = "default";
    static readonly Emphasis = "emphasis";
}

export enum ValidationError {
    Hint,
    ActionTypeNotAllowed,
    CollectionCantBeEmpty,
    Deprecated,
    ElementTypeNotAllowed,
    InteractivityNotAllowed,
    InvalidPropertyValue,
    MissingCardType,
    PropertyCantBeNull,
    TooManyActions,
    UnknownActionType,
    UnknownElementType,
    UnsupportedCardVersion
}

export enum ContainerFitStatus {
    FullyInContainer,
    Overflowing,
    FullyOutOfContainer
}
