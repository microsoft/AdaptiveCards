#pragma once
#include "pch.h"
#include "EnumMagic.h"

namespace AdaptiveSharedNamespace
{
    enum class AdaptiveCardSchemaKey
    {
        Accent = 0,
        ActionAlignment,
        ActionMode,
        ActionOrientation,
        ActionSet,
        ActionSetConfig,
        Actions,
        ActionsOrientation,
        AdaptiveCard,
        AllowCustomStyle,
        AllowInlinePlayback,
        AltText,
        Attention,
        BackgroundColor,
        BackgroundImage,
        BackgroundImageUrl,
        BaseCardElement,
        Body,
        Bolder,
        BorderColor,
        BorderThickness,
        Bottom,
        ButtonSpacing,
        Card,
        Center,
        ChoiceSet,
        Choices,
        Color,
        ColorConfig,
        Column,
        ColumnSet,
        Columns,
        Container,
        ContainerStyles,
        Dark,
        Data,
        DateInput,
        Default,
        DefaultPoster,
        Display,
        ElementId,
        Emphasis,
        ExtraLarge,
        FactSet,
        Facts,
        Fallback,
        FallbackText,
        FontFamily,
        FontSizes,
        FontStyle,
        FontStyles,
        FontWeights,
        ForegroundColors,
        Good,
        Height,
        HorizontalAlignment,
        IconPlacement,
        IconSize,
        IconUrl,
        Id,
        Image,
        ImageBaseUrl,
        ImageSet,
        ImageSize,
        ImageSizes,
        Images,
        InlineAction,
        InlineTopMargin,
        IsMultiSelect,
        IsMultiline,
        IsRequired,
        IsSelected,
        IsSubtle,
        IsVisible,
        Items,
        Language,
        Large,
        Left,
        Light,
        Lighter,
        LineColor,
        LineThickness,
        Max,
        MaxActions,
        MaxImageHeight,
        MaxLength,
        MaxLines,
        MaxWidth,
        Media,
        Medium,
        Method,
        MimeType,
        Min,
        Monospace,
        NumberInput,
        Padding,
        Placeholder,
        PlayButton,
        Poster,
        Requires,
        Right,
        SelectAction,
        Sentiment,
        Separator,
        ShowActionMode,
        ShowCard,
        ShowCardActionConfig,
        Size,
        Small,
        Sources,
        Spacing,
        SpacingDefinition,
        Speak,
        Stretch,
        Style,
        Subtle,
        SupportsInteractivity,
        TargetElements,
        Text,
        TextBlock,
        TextConfig,
        TextInput,
        TextWeight,
        Thickness,
        TimeInput,
        Title,
        ToggleInput,
        Top,
        Type,
        Url,
        Value,
        ValueOff,
        ValueOn,
        Version,
        VerticalContentAlignment,
        Warning,
        Weight,
        Width,
        Wrap,
    };
    DECLARE_ADAPTIVECARD_ENUM(AdaptiveCardSchemaKey);

    enum class CardElementType
    {
        // When the order of existing enums are changed, coresponding changes are needed in iOS (ACOBaseCardElement.h)
        ActionSet = 0,
        AdaptiveCard,
        ChoiceInput,
        ChoiceSetInput,
        Column,
        ColumnSet,
        Container,
        Custom,
        DateInput,
        Fact,
        FactSet,
        Image,
        ImageSet,
        Media,
        NumberInput,
        TextBlock,
        TextInput,
        TimeInput,
        ToggleInput,
        Unknown,
    };
    DECLARE_ADAPTIVECARD_ENUM(CardElementType);

    enum class TextSize
    {
        Small = 0,
        Default,
        Medium,
        Large,
        ExtraLarge
    };
    DECLARE_ADAPTIVECARD_ENUM(TextSize);

    enum class TextWeight
    {
        Lighter = 0,
        Default,
        Bolder
    };
    DECLARE_ADAPTIVECARD_ENUM(TextWeight);

    enum class FontStyle
    {
        Default = 0,
        Display,
        Monospace
    };
    DECLARE_ADAPTIVECARD_ENUM(FontStyle);

    enum class ForegroundColor
    {
        Default = 0,
        Dark,
        Light,
        Accent,
        Good,
        Warning,
        Attention
    };
    DECLARE_ADAPTIVECARD_ENUM(ForegroundColor);

    enum class HorizontalAlignment
    {
        Left = 0,
        Center,
        Right
    };
    DECLARE_ADAPTIVECARD_ENUM(HorizontalAlignment);

    enum class ImageStyle
    {
        Default = 0,
        Person
    };
    DECLARE_ADAPTIVECARD_ENUM(ImageStyle);

    enum class ImageSize
    {
        None = 0,
        Auto,
        Stretch,
        Small,
        Medium,
        Large,
    };
    DECLARE_ADAPTIVECARD_ENUM(ImageSize);

    enum class TextInputStyle
    {
        Text = 0,
        Tel,
        Url,
        Email,
    };
    DECLARE_ADAPTIVECARD_ENUM(TextInputStyle);

    enum class ActionType
    {
        Unsupported = 0,
        ShowCard,
        Submit,
        OpenUrl,
        ToggleVisibility,
        Custom,
        UnknownAction,
    };
    DECLARE_ADAPTIVECARD_ENUM(ActionType);

    enum class ActionAlignment
    {
        Left = 0,
        Center,
        Right,
        Stretch,
    };
    DECLARE_ADAPTIVECARD_ENUM(ActionAlignment);

    enum class ChoiceSetStyle
    {
        Compact = 0,
        Expanded
    };
    DECLARE_ADAPTIVECARD_ENUM(ChoiceSetStyle);

    enum class SeparatorThickness
    {
        Default = 0,
        Thick,
    };
    DECLARE_ADAPTIVECARD_ENUM(SeparatorThickness);

    enum class Spacing
    {
        Default = 0,
        None,
        Small,
        Medium,
        Large,
        ExtraLarge,
        Padding
    };
    DECLARE_ADAPTIVECARD_ENUM(Spacing);

    enum class ActionsOrientation
    {
        Vertical = 0,
        Horizontal
    };
    DECLARE_ADAPTIVECARD_ENUM(ActionsOrientation);

    enum class ActionMode
    {
        Inline = 0,
        Popup
    };
    DECLARE_ADAPTIVECARD_ENUM(ActionMode);

    enum class ContainerStyle
    {
        None,
        Default,
        Emphasis
    };
    DECLARE_ADAPTIVECARD_ENUM(ContainerStyle);

    enum class ErrorStatusCode
    {
        InvalidJson = 0,
        RenderFailed,
        RequiredPropertyMissing,
        InvalidPropertyValue,
        UnsupportedParserOverride,
        IdCollision
    };
    // No mapping to string needed

    enum class WarningStatusCode
    {
        UnknownElementType = 0,
        UnknownActionElementType,
        UnknownPropertyOnElement,
        UnknownEnumValue,
        NoRendererForType,
        InteractivityNotSupported,
        MaxActionsExceeded,
        AssetLoadFailed,
        UnsupportedSchemaVersion,
        UnsupportedMediaType,
        InvalidMediaMix,
        InvalidColorFormat,
        InvalidDimensionSpecified,
        InvalidLanguage,
    };
    // No mapping to string needed

    enum class DateTimePreparsedTokenFormat
    {
        RegularString = 0,
        Time,
        DateCompact,
        DateShort,
        DateLong
    };
    // No mapping to string needed

    enum class IconPlacement
    {
        AboveTitle = 0,
        LeftOfTitle
    };
    DECLARE_ADAPTIVECARD_ENUM(IconPlacement);

    enum class VerticalContentAlignment
    {
        Top = 0,
        Center,
        Bottom
    };
    DECLARE_ADAPTIVECARD_ENUM(VerticalContentAlignment);

    enum class HeightType
    {
        Auto = 0,
        Stretch
    };
    DECLARE_ADAPTIVECARD_ENUM(HeightType);

    // Important: "Content" below is a placeholder for a JSON value -- we can't perform automatic mapping.
    enum class FallbackType
    {
        None,
        Drop,
        Content
    };
}
