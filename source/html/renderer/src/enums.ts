export type Size = "auto" | "stretch" | "small" | "medium" | "large";

export type TextSize = "small" | "normal" | "medium" | "large" | "extraLarge";

export type Spacing = "none" | "small" | "default" | "medium" | "large" | "extraLarge" | "padding";

export type Padding = "none" | "default";

export type TextWeight = "lighter" | "normal" | "bolder";

export type TextColor = "default" | "accent" | "good" | "warning" | "attention";

export type HorizontalAlignment = "left" | "center" | "right";

export type VerticalAlignment = "top" | "center" | "bottom";

export type ActionAlignment = "left" | "center" | "right" | "stretch";

export type ActionStyle = "button" | "link";

export type ImageStyle = "normal" | "person";

export type ShowCardActionMode = "inline" | "inlineEdgeToEdge" | "popup";

export type Orientation = "horizontal" | "vertical";

export type BackgroundImageMode = "stretch" | "repeatHorizontally" | "repeatVertically" | "repeat";

export type ContainerStyle = "default" | "emphasis";

export enum ValidationError {
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