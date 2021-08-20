// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "pch.h"
#include "EnumMagic.h"

namespace AdaptiveCards
{
    enum class AdaptiveCardSchemaKey
    {
        Accent = 0,
        Action,
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
        AssociatedInputs,
        Attention,
        Authentication,
        BackgroundColor,
        BackgroundImage,
        BackgroundImageUrl,
        BaseCardElement,
        BaseContainerStyle,
        Bleed,
        Body,
        Bolder,
        BorderColor,
        BorderThickness,
        Bottom,
        ButtonSpacing,
        Buttons,
        Card,
        CellSpacing,
        Cells,
        Center,
        ChoiceSet,
        Choices,
        Color,
        ColorConfig,
        Column,
        ColumnHeader,
        ColumnSet,
        Columns,
        ConnectionName,
        Container,
        ContainerStyles,
        Dark,
        Data,
        DateInput,
        Default,
        DefaultPoster,
        ElementId,
        Emphasis,
        ErrorMessage,
        ExtraLarge,
        FactSet,
        Facts,
        Fallback,
        FallbackText,
        FillMode,
        FirstRowAsHeaders,
        FontFamily,
        FontSizes,
        FontType,
        FontTypes,
        FontWeights,
        ForegroundColor,
        ForegroundColors,
        Good,
        GridStyle,
        Heading,
        HeadingLevel,
        Height,
        Highlight,
        HighlightColor,
        HighlightColors,
        HorizontalAlignment,
        HorizontalCellContentAlignment,
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
        Inlines,
        InputSpacing,
        Inputs,
        IsEnabled,
        IsMultiSelect,
        IsMultiline,
        IsRequired,
        IsSelected,
        IsSubtle,
        IsVisible,
        Italic,
        Items,
        Label,
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
        MinHeight,
        Mode,
        Monospace,
        NumberInput,
        OptionalInputs,
        Padding,
        Placeholder,
        PlayButton,
        Poster,
        ProviderId,
        Refresh,
        Regex,
        Repeat,
        RepeatHorizontally,
        RepeatVertically,
        RequiredInputs,
        Requires,
        RichTextBlock,
        Right,
        Rows,
        Rtl,
        Schema,
        SelectAction,
        Separator,
        ShowActionMode,
        ShowCard,
        ShowCardActionConfig,
        ShowGridLines,
        Size,
        Small,
        Sources,
        Spacing,
        SpacingDefinition,
        Speak,
        Stretch,
        Strikethrough,
        Style,
        Subtle,
        Suffix,
        SupportsInteractivity,
        Table,
        TableCell,
        TableRow,
        TargetElements,
        Text,
        TextBlock,
        TextConfig,
        TextInput,
        TextStyles,
        TextWeight,
        Thickness,
        TimeInput,
        Title,
        ToggleInput,
        TokenExchangeResource,
        Tooltip,
        Top,
        Type,
        Underline,
        Uri,
        Url,
        UserIds,
        Value,
        ValueOff,
        ValueOn,
        Verb,
        Version,
        VerticalAlignment,
        VerticalCellContentAlignment,
        VerticalContentAlignment,
        Warning,
        Weight,
        Width,
        Wrap,
    };
    DECLARE_ADAPTIVECARD_ENUM(AdaptiveCardSchemaKey);

    enum class CardElementType
    {
        // When the order of existing enums are changed, corresponding changes are needed in iOS (ACOBaseCardElement.h)
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
        RichTextBlock,
        Table,
        TableCell,
        TableRow,
        TextBlock,
        TextInput,
        TimeInput,
        ToggleInput,
        Unknown,
    };
    DECLARE_ADAPTIVECARD_ENUM(CardElementType);

    enum class InlineElementType
    {
        TextRun = 0
    };
    DECLARE_ADAPTIVECARD_ENUM(InlineElementType);

    enum class TextStyle
    {
        Default = 0,
        Heading
    };
    DECLARE_ADAPTIVECARD_ENUM(TextStyle);

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

    enum class FontType
    {
        Default = 0,
        Monospace
    };
    DECLARE_ADAPTIVECARD_ENUM(FontType);

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

    enum class VerticalAlignment
    {
        Top = 0,
        Center,
        Bottom
    };
    DECLARE_ADAPTIVECARD_ENUM(VerticalAlignment);

    enum class ImageFillMode
    {
        Cover = 0,
        RepeatHorizontally,
        RepeatVertically,
        Repeat
    };
    DECLARE_ADAPTIVECARD_ENUM(ImageFillMode);

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
        Execute,
        OpenUrl,
        ShowCard,
        Submit,
        ToggleVisibility,
        Custom,
        UnknownAction,
        Overflow
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

    enum class AssociatedInputs
    {
        Auto = 0,
        None
    };
    DECLARE_ADAPTIVECARD_ENUM(AssociatedInputs);

    enum class ChoiceSetStyle
    {
        Compact = 0,
        Expanded,
        Filtered
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
        Emphasis,
        Good,
        Attention,
        Warning,
        Accent
    };
    DECLARE_ADAPTIVECARD_ENUM(ContainerStyle);

    enum class Mode
    {
        Primary = 0,
        Secondary
    };
    DECLARE_ADAPTIVECARD_ENUM(Mode);

    enum class ErrorStatusCode
    {
        InvalidJson = 0,
        RenderFailed,
        RequiredPropertyMissing,
        InvalidPropertyValue,
        UnsupportedParserOverride,
        IdCollision,
        CustomError,
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
        InvalidValue,
        CustomWarning,
        EmptyLabelInRequiredInput,
        RequiredPropertyMissing,
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

    // We have to define all possible combinations because java doesn't allow bitwise operations between enum values
    // and it also limits the values an enum can have to only the values defined in the enum, so combinations wouldn't be
    // allowed unless they have been explicitly declared (i.e. 0x0101 wouldn't be valid as it was not part of the declared values)
    enum class ContainerBleedDirection
    {
        BleedRestricted = 0x0000,
        BleedLeft = 0x0001,
        BleedRight = 0x0010,
        BleedLeftRight = 0x0011,
        BleedUp = 0x0100,
        BleedLeftUp = 0x0101,
        BleedRightUp = 0x0110,
        BleedLeftRightUp = 0x0111,
        BleedDown = 0x1000,
        BleedLeftDown = 0x1001,
        BleedRightDown = 0x1010,
        BleedLeftRightDown = 0x1011,
        BleedUpDown = 0x1100,
        BleedLeftUpDown = 0x1101,
        BleedRightUpDown = 0x1110,
        BleedAll = 0x1111
    };

    // Define bit operators so we can use ContainerBleedDirection as a bitmask
    inline ContainerBleedDirection operator~(ContainerBleedDirection a) { return (ContainerBleedDirection) ~(int)a; }
    inline ContainerBleedDirection operator|(ContainerBleedDirection a, ContainerBleedDirection b)
    {
        return (ContainerBleedDirection)((int)a | (int)b);
    }
    inline ContainerBleedDirection operator&(ContainerBleedDirection a, ContainerBleedDirection b)
    {
        return (ContainerBleedDirection)((int)a & (int)b);
    }
    inline ContainerBleedDirection& operator|=(ContainerBleedDirection& a, ContainerBleedDirection b)
    {
        return (ContainerBleedDirection&)((int&)a |= (int)b);
    }
    inline ContainerBleedDirection& operator&=(ContainerBleedDirection& a, ContainerBleedDirection b)
    {
        return (ContainerBleedDirection&)((int&)a &= (int)b);
    }

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
