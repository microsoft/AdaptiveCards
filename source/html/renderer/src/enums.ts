export type Size = "auto" | "stretch" | "small" | "medium" | "large";

export type TextSize = "small" | "normal" | "medium" | "large" | "extraLarge";

export type TextWeight = "lighter" | "normal" | "bolder";

export type TextColor = "dark" | "light" | "accent" | "good" | "warning" | "attention";

export type HorizontalAlignment = "left" | "center" | "right";

export type ActionAlignment = "left" | "center" | "right" | "stretch";

export type ContainerStyle = "normal" | "emphasis";

export type ImageStyle = "normal" | "person";

export type Separation = "none" | "default" | "strong";

export type ShowCardActionMode = "inline" | "inlineEdgeToEdge" | "popup";

export type Orientation = "horizontal" | "vertical";

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