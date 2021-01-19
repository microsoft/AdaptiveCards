// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// Note the "weird" way these readonly fields are declared is to work around
// a breaking change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
// and adopt this syntax for all other static readonly fields.
export class ActionStyle {
    static readonly Default: "default" = "default";
    static readonly Positive: "positive" = "positive";
    static readonly Destructive: "destructive" = "destructive";
}

export enum Size {
    Auto,
    Stretch,
    Small,
    Medium,
    Large
}

export enum ImageSize {
    Small,
    Medium,
    Large
}

export enum SizeUnit {
    Weight,
    Pixel
}

export enum TextSize {
    Small,
    Default,
    Medium,
    Large,
    ExtraLarge
}

export enum TextWeight {
    Lighter,
    Default,
    Bolder
}

export enum FontType {
    Default,
    Monospace
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

export enum FillMode {
    Cover,
    RepeatHorizontally,
    RepeatVertically,
    Repeat
}

export enum ActionIconPlacement {
    LeftOfTitle,
    AboveTitle
}

export enum InputTextStyle {
    Text,
    Tel,
    Url,
    Email
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

    Also note the "weird" way these readonly fields are declared is to work around
    a breaking change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
    and adopt this syntax for all other static readonly fields.
*/
export class ContainerStyle {
    static readonly Default: "default" = "default";
    static readonly Emphasis: "emphasis" = "emphasis";
    static readonly Accent: "accent" = "accent";
    static readonly Good: "good" = "good";
    static readonly Attention: "attention" = "attention";
    static readonly Warning: "warning" = "warning";
}

export enum ValidationPhase {
    Parse,
    ToJSON,
    Validation
}

export enum ValidationEvent {
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
    UnsupportedCardVersion,
    DuplicateId,
    UnsupportedProperty,
    RequiredInputsShouldHaveLabel,
    RequiredInputsShouldHaveErrorMessage,
    Other
}

export enum ContainerFitStatus {
    FullyInContainer,
    Overflowing,
    FullyOutOfContainer
}
