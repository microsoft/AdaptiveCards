// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "HostConfig.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

HostConfig HostConfig::DeserializeFromString(const std::string& jsonString)
{
    return HostConfig::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

HostConfig HostConfig::Deserialize(const Json::Value& json)
{
    HostConfig result;
    std::string fontFamily = ParseUtil::GetString(json, AdaptiveCardSchemaKey::FontFamily);
    result._fontFamily = fontFamily != "" ? fontFamily : result._fontFamily;

    result._supportsInteractivity =
        ParseUtil::GetBool(json, AdaptiveCardSchemaKey::SupportsInteractivity, result._supportsInteractivity);

    result._imageBaseUrl = ParseUtil::GetString(json, AdaptiveCardSchemaKey::ImageBaseUrl);

    result._factSet = ParseUtil::ExtractJsonValueAndMergeWithDefault<FactSetConfig>(json,
                                                                                    AdaptiveCardSchemaKey::FactSet,
                                                                                    result._factSet,
                                                                                    FactSetConfig::Deserialize);

    result._fontSizes = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontSizesConfig>(json,
                                                                                        AdaptiveCardSchemaKey::FontSizes,
                                                                                        result._fontSizes,
                                                                                        FontSizesConfig::Deserialize);

    result._fontWeights = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontWeightsConfig>(
        json, AdaptiveCardSchemaKey::FontWeights, result._fontWeights, FontWeightsConfig::Deserialize);

    result._fontTypes = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontTypesDefinition>(
        json, AdaptiveCardSchemaKey::FontTypes, result._fontTypes, FontTypesDefinition::Deserialize);

    result._containerStyles = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStylesDefinition>(
        json, AdaptiveCardSchemaKey::ContainerStyles, result._containerStyles, ContainerStylesDefinition::Deserialize);

    result._image =
        ParseUtil::ExtractJsonValueAndMergeWithDefault<ImageConfig>(json, AdaptiveCardSchemaKey::Image, result._image, ImageConfig::Deserialize);

    result._imageSet = ParseUtil::ExtractJsonValueAndMergeWithDefault<ImageSetConfig>(json,
                                                                                      AdaptiveCardSchemaKey::ImageSet,
                                                                                      result._imageSet,
                                                                                      ImageSetConfig::Deserialize);

    result._imageSizes = ParseUtil::ExtractJsonValueAndMergeWithDefault<ImageSizesConfig>(json,
                                                                                          AdaptiveCardSchemaKey::ImageSizes,
                                                                                          result._imageSizes,
                                                                                          ImageSizesConfig::Deserialize);

    result._separator = ParseUtil::ExtractJsonValueAndMergeWithDefault<SeparatorConfig>(json,
                                                                                        AdaptiveCardSchemaKey::Separator,
                                                                                        result._separator,
                                                                                        SeparatorConfig::Deserialize);

    result._spacing = ParseUtil::ExtractJsonValueAndMergeWithDefault<SpacingConfig>(json,
                                                                                    AdaptiveCardSchemaKey::Spacing,
                                                                                    result._spacing,
                                                                                    SpacingConfig::Deserialize);

    result._adaptiveCard = ParseUtil::ExtractJsonValueAndMergeWithDefault<AdaptiveCardConfig>(
        json, AdaptiveCardSchemaKey::AdaptiveCard, result._adaptiveCard, AdaptiveCardConfig::Deserialize);

    result._actions = ParseUtil::ExtractJsonValueAndMergeWithDefault<ActionsConfig>(json,
                                                                                    AdaptiveCardSchemaKey::Actions,
                                                                                    result._actions,
                                                                                    ActionsConfig::Deserialize);

    result._media =
        ParseUtil::ExtractJsonValueAndMergeWithDefault<MediaConfig>(json, AdaptiveCardSchemaKey::Media, result._media, MediaConfig::Deserialize);

    result._inputs = ParseUtil::ExtractJsonValueAndMergeWithDefault<InputsConfig>(json,
                                                                                  AdaptiveCardSchemaKey::Inputs,
                                                                                  result._inputs,
                                                                                  InputsConfig::Deserialize);

    return result;
}

FontSizesConfig FontSizesConfig::Deserialize(const Json::Value& json, const FontSizesConfig& defaultValue)
{
    FontSizesConfig result;
    result._small = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Small, defaultValue._small);
    result._default = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Default, defaultValue._default);
    result._medium = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Medium, defaultValue._medium);
    result._large = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Large, defaultValue._large);
    result._extraLarge = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::ExtraLarge, defaultValue._extraLarge);
    return result;
}

FontTypeDefinition FontTypeDefinition::Deserialize(const Json::Value& json, const FontTypeDefinition& defaultValue)
{
    FontTypeDefinition result;

    const std::string fontFamily = ParseUtil::GetString(json, AdaptiveCardSchemaKey::FontFamily);
    result.fontFamily = (fontFamily == "") ? defaultValue.fontFamily : fontFamily;

    result.fontSizes = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontSizesConfig>(json,
                                                                                       AdaptiveCardSchemaKey::FontSizes,
                                                                                       defaultValue.fontSizes,
                                                                                       FontSizesConfig::Deserialize);

    result.fontWeights = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontWeightsConfig>(json,
                                                                                           AdaptiveCardSchemaKey::FontWeights,
                                                                                           defaultValue.fontWeights,
                                                                                           FontWeightsConfig::Deserialize);

    return result;
}

FontTypesDefinition FontTypesDefinition::Deserialize(const Json::Value& json, const FontTypesDefinition& defaultValue)
{
    FontTypesDefinition result;

    result.defaultFontType = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontTypeDefinition>(
        json, AdaptiveCardSchemaKey::Default, defaultValue.defaultFontType, FontTypeDefinition::Deserialize);
    result.monospaceFontType = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontTypeDefinition>(
        json, AdaptiveCardSchemaKey::Monospace, defaultValue.monospaceFontType, FontTypeDefinition::Deserialize);
    return result;
}

HighlightColorConfig HighlightColorConfig::Deserialize(const Json::Value& json, const HighlightColorConfig& defaultValue)
{
    HighlightColorConfig result;
    std::string defaultColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Default);
    result.defaultColor = defaultColor == "" ? defaultValue.defaultColor : defaultColor;

    std::string subtleColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Subtle);
    result.subtleColor = subtleColor == "" ? defaultValue.subtleColor : subtleColor;

    return result;
}

ColorConfig ColorConfig::Deserialize(const Json::Value& json, const ColorConfig& defaultValue)
{
    ColorConfig result;
    std::string defaultColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Default);
    result.defaultColor = defaultColor == "" ? defaultValue.defaultColor : defaultColor;

    std::string subtleColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Subtle);
    result.subtleColor = subtleColor == "" ? defaultValue.subtleColor : subtleColor;

    result.highlightColors = ParseUtil::ExtractJsonValueAndMergeWithDefault<HighlightColorConfig>(
        json, AdaptiveCardSchemaKey::HighlightColors, defaultValue.highlightColors, HighlightColorConfig::Deserialize);

    return result;
}

ColorsConfig ColorsConfig::Deserialize(const Json::Value& json, const ColorsConfig& defaultValue)
{
    ColorsConfig result;

    result.defaultColor = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json,
                                                                                      AdaptiveCardSchemaKey::Default,
                                                                                      defaultValue.defaultColor,
                                                                                      &ColorConfig::Deserialize);

    result.accent = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json,
                                                                                AdaptiveCardSchemaKey::Accent,
                                                                                defaultValue.accent,
                                                                                &ColorConfig::Deserialize);

    result.dark = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json,
                                                                              AdaptiveCardSchemaKey::Dark,
                                                                              defaultValue.dark,
                                                                              &ColorConfig::Deserialize);

    result.light = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json,
                                                                               AdaptiveCardSchemaKey::Light,
                                                                               defaultValue.light,
                                                                               &ColorConfig::Deserialize);

    result.good = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json,
                                                                              AdaptiveCardSchemaKey::Good,
                                                                              defaultValue.good,
                                                                              &ColorConfig::Deserialize);

    result.warning = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json,
                                                                                 AdaptiveCardSchemaKey::Warning,
                                                                                 defaultValue.warning,
                                                                                 &ColorConfig::Deserialize);

    result.attention = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json,
                                                                                   AdaptiveCardSchemaKey::Attention,
                                                                                   defaultValue.attention,
                                                                                   &ColorConfig::Deserialize);
    return result;
}

TextConfig TextConfig::Deserialize(const Json::Value& json, const TextConfig& defaultValue)
{
    TextConfig result;
    result.weight = ParseUtil::GetEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::Weight, defaultValue.weight, TextWeightFromString);

    result.size = ParseUtil::GetEnumValue<TextSize>(json, AdaptiveCardSchemaKey::Size, defaultValue.size, TextSizeFromString);

    result.fontType = ParseUtil::GetEnumValue<FontType>(json, AdaptiveCardSchemaKey::FontType, defaultValue.fontType, FontTypeFromString);

    result.color = ParseUtil::GetEnumValue<ForegroundColor>(json, AdaptiveCardSchemaKey::Color, defaultValue.color, ForegroundColorFromString);

    result.isSubtle = ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsSubtle, defaultValue.isSubtle);

    result.wrap = ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Wrap, defaultValue.wrap);

    result.maxWidth = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxWidth, defaultValue.maxWidth);

    return result;
}

ImageSizesConfig ImageSizesConfig::Deserialize(const Json::Value& json, const ImageSizesConfig& defaultValue)
{
    ImageSizesConfig result;
    result.smallSize = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Small, defaultValue.smallSize);
    result.mediumSize = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Medium, defaultValue.mediumSize);
    result.largeSize = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Large, defaultValue.largeSize);

    return result;
}

AdaptiveCardConfig AdaptiveCardConfig::Deserialize(const Json::Value& json, const AdaptiveCardConfig& defaultValue)
{
    AdaptiveCardConfig result;
    result.allowCustomStyle = ParseUtil::GetBool(json, AdaptiveCardSchemaKey::AllowCustomStyle, defaultValue.allowCustomStyle);

    return result;
}

ImageSetConfig ImageSetConfig::Deserialize(const Json::Value& json, const ImageSetConfig& defaultValue)
{
    ImageSetConfig result;
    result.imageSize =
        ParseUtil::GetEnumValue<ImageSize>(json, AdaptiveCardSchemaKey::ImageSize, defaultValue.imageSize, ImageSizeFromString);

    result.maxImageHeight = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxImageHeight, defaultValue.maxImageHeight);

    return result;
}

FactSetConfig FactSetConfig::Deserialize(const Json::Value& json, const FactSetConfig& defaultValue)
{
    FactSetConfig result;

    result.spacing = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Spacing, defaultValue.spacing);
    result.title = ParseUtil::ExtractJsonValueAndMergeWithDefault<TextConfig>(json,
                                                                              AdaptiveCardSchemaKey::Title,
                                                                              defaultValue.title,
                                                                              TextConfig::Deserialize);

    result.value = ParseUtil::ExtractJsonValueAndMergeWithDefault<TextConfig>(json,
                                                                              AdaptiveCardSchemaKey::Value,
                                                                              defaultValue.value,
                                                                              TextConfig::Deserialize);

    // Value doesn't support maxWidth, so reset to the default value.
    result.value.maxWidth = defaultValue.value.maxWidth;

    return result;
}

ShowCardActionConfig ShowCardActionConfig::Deserialize(const Json::Value& json, const ShowCardActionConfig& defaultValue)
{
    ShowCardActionConfig result;
    result.actionMode =
        ParseUtil::GetEnumValue<ActionMode>(json, AdaptiveCardSchemaKey::ActionMode, defaultValue.actionMode, ActionModeFromString);
    result.inlineTopMargin = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::InlineTopMargin, defaultValue.inlineTopMargin);
    result.style = ParseUtil::GetEnumValue<ContainerStyle>(json, AdaptiveCardSchemaKey::Style, defaultValue.style, ContainerStyleFromString);

    return result;
}

ActionsConfig ActionsConfig::Deserialize(const Json::Value& json, const ActionsConfig& defaultValue)
{
    ActionsConfig result;

    result.actionsOrientation = ParseUtil::GetEnumValue<ActionsOrientation>(json,
                                                                            AdaptiveCardSchemaKey::ActionsOrientation,
                                                                            defaultValue.actionsOrientation,
                                                                            ActionsOrientationFromString);

    result.actionAlignment =
        ParseUtil::GetEnumValue<ActionAlignment>(json, AdaptiveCardSchemaKey::ActionAlignment, defaultValue.actionAlignment, ActionAlignmentFromString);

    result.buttonSpacing = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::ButtonSpacing, defaultValue.buttonSpacing);

    result.maxActions = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxActions, defaultValue.maxActions);

    result.showCard = ParseUtil::ExtractJsonValueAndMergeWithDefault<ShowCardActionConfig>(
        json, AdaptiveCardSchemaKey::ShowCard, defaultValue.showCard, ShowCardActionConfig::Deserialize);

    result.spacing = ParseUtil::GetEnumValue<Spacing>(json, AdaptiveCardSchemaKey::Spacing, defaultValue.spacing, SpacingFromString);

    result.iconPlacement =
        ParseUtil::GetEnumValue<IconPlacement>(json, AdaptiveCardSchemaKey::IconPlacement, defaultValue.iconPlacement, IconPlacementFromString);

    result.iconSize = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::IconSize, defaultValue.iconSize);

    return result;
}

InputLabelConfig InputLabelConfig::Deserialize(const Json::Value& json, const InputLabelConfig& defaultValue)
{
    InputLabelConfig result;

    result.color = ParseUtil::GetEnumValue<ForegroundColor>(json, AdaptiveCardSchemaKey::Color, defaultValue.color, ForegroundColorFromString);

    result.isSubtle = ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsSubtle, defaultValue.isSubtle);

    result.size = ParseUtil::GetEnumValue<TextSize>(json, AdaptiveCardSchemaKey::Size, defaultValue.size, TextSizeFromString);
    
    result.weight = ParseUtil::GetEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::Weight, defaultValue.weight, TextWeightFromString);

    return result;
}

InputLabelsConfig InputLabelsConfig::Deserialize(const Json::Value& json, const InputLabelsConfig& defaultValue)
{
    InputLabelsConfig result;

    result.inputSpacing = ParseUtil::GetEnumValue<Spacing>(json, AdaptiveCardSchemaKey::InputSpacing, defaultValue.inputSpacing, SpacingFromString);

    result.requiredSuffix = ParseUtil::GetString(json, AdaptiveCardSchemaKey::RequiredSuffix, defaultValue.requiredSuffix);

    result.requiredInputs = ParseUtil::ExtractJsonValueAndMergeWithDefault<InputLabelConfig>(json,
                                                                                             AdaptiveCardSchemaKey::RequiredInputs,
                                                                                             defaultValue.requiredInputs,
                                                                                             InputLabelConfig::Deserialize);

    result.optionalInputs = ParseUtil::ExtractJsonValueAndMergeWithDefault<InputLabelConfig>(json,
                                                                                             AdaptiveCardSchemaKey::OptionalInputs,
                                                                                             defaultValue.optionalInputs,
                                                                                             InputLabelConfig::Deserialize);

    return result;
}

ErrorMessageConfig ErrorMessageConfig::Deserialize(const Json::Value& json, const ErrorMessageConfig& defaultValue)
{
    ErrorMessageConfig result;

    result.size = ParseUtil::GetEnumValue<TextSize>(json, AdaptiveCardSchemaKey::Size, defaultValue.size, TextSizeFromString);

    result.spacing = ParseUtil::GetEnumValue<Spacing>(json, AdaptiveCardSchemaKey::Spacing, defaultValue.spacing, SpacingFromString);

    result.weight = ParseUtil::GetEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::Weight, defaultValue.weight, TextWeightFromString);

    return result;
}

InputsConfig InputsConfig::Deserialize(const Json::Value& json, const InputsConfig& defaultValue)
{
    InputsConfig result;

    result.errorMessage = ParseUtil::ExtractJsonValueAndMergeWithDefault<ErrorMessageConfig>(json,
                                                                                             AdaptiveCardSchemaKey::ErrorMessage,
                                                                                             defaultValue.errorMessage,
                                                                                             ErrorMessageConfig::Deserialize);

    result.inputLabels = ParseUtil::ExtractJsonValueAndMergeWithDefault<InputLabelsConfig>(json,
                                                                                           AdaptiveCardSchemaKey::InputLabels,
                                                                                           defaultValue.inputLabels,
                                                                                           InputLabelsConfig::Deserialize);

    result.validationBehavior = ParseUtil::GetEnumValue<ValidationBehavior>(json,
                                                                            AdaptiveCardSchemaKey::ValidationBehavior,
                                                                            defaultValue.validationBehavior,
                                                                            ValidationBehaviorFromString);

    return result;
}


SpacingConfig SpacingConfig::Deserialize(const Json::Value& json, const SpacingConfig& defaultValue)
{
    SpacingConfig result;

    result.smallSpacing = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Small, defaultValue.smallSpacing);

    result.defaultSpacing = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Default, defaultValue.defaultSpacing);

    result.mediumSpacing = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Medium, defaultValue.mediumSpacing);

    result.largeSpacing = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Large, defaultValue.largeSpacing);

    result.extraLargeSpacing = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::ExtraLarge, defaultValue.extraLargeSpacing);

    result.paddingSpacing = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Padding, defaultValue.paddingSpacing);

    return result;
}

SeparatorConfig SeparatorConfig::Deserialize(const Json::Value& json, const SeparatorConfig& defaultValue)
{
    SeparatorConfig result;

    result.lineThickness = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::LineThickness, defaultValue.lineThickness);

    std::string lineColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::LineColor);
    result.lineColor = lineColor == "" ? defaultValue.lineColor : lineColor;

    return result;
}

ContainerStyleDefinition ContainerStyleDefinition::Deserialize(const Json::Value& json, const ContainerStyleDefinition& defaultValue)
{
    ContainerStyleDefinition result;

    const std::string backgroundColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::BackgroundColor);
    result.backgroundColor = backgroundColor == "" ? defaultValue.backgroundColor : backgroundColor;

    const std::string borderColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::BorderColor);
    result.borderColor = borderColor == "" ? defaultValue.borderColor : borderColor;

    result.borderThickness = ParseUtil::GetInt(json, AdaptiveCardSchemaKey::BorderThickness, defaultValue.borderThickness);

    result.foregroundColors = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorsConfig>(
        json, AdaptiveCardSchemaKey::ForegroundColors, defaultValue.foregroundColors, ColorsConfig::Deserialize);

    return result;
}

ContainerStylesDefinition ContainerStylesDefinition::Deserialize(const Json::Value& json, const ContainerStylesDefinition& defaultValue)
{
    ContainerStylesDefinition result;

    result.defaultPalette = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStyleDefinition>(
        json, AdaptiveCardSchemaKey::Default, defaultValue.defaultPalette, ContainerStyleDefinition::Deserialize);

    result.emphasisPalette = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStyleDefinition>(
        json, AdaptiveCardSchemaKey::Emphasis, defaultValue.emphasisPalette, ContainerStyleDefinition::Deserialize);

    result.goodPalette = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStyleDefinition>(
        json, AdaptiveCardSchemaKey::Good, defaultValue.goodPalette, ContainerStyleDefinition::Deserialize);

    result.attentionPalette = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStyleDefinition>(
        json, AdaptiveCardSchemaKey::Attention, defaultValue.attentionPalette, ContainerStyleDefinition::Deserialize);

    result.warningPalette = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStyleDefinition>(
        json, AdaptiveCardSchemaKey::Warning, defaultValue.warningPalette, ContainerStyleDefinition::Deserialize);

    result.accentPalette = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStyleDefinition>(
        json, AdaptiveCardSchemaKey::Accent, defaultValue.accentPalette, ContainerStyleDefinition::Deserialize);

    return result;
}

FontWeightsConfig FontWeightsConfig::Deserialize(const Json::Value& json, const FontWeightsConfig& defaultValue)
{
    FontWeightsConfig result;

    result._lighter = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Lighter, defaultValue._lighter);

    result._default = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Default, defaultValue._default);

    result._bolder = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Bolder, defaultValue._bolder);

    return result;
}

ImageConfig ImageConfig::Deserialize(const Json::Value& json, const ImageConfig& defaultValue)
{
    ImageConfig result;

    result.imageSize =
        ParseUtil::GetEnumValue<ImageSize>(json, AdaptiveCardSchemaKey::Size, defaultValue.imageSize, ImageSizeFromString);

    return result;
}

MediaConfig MediaConfig::Deserialize(const Json::Value& json, const MediaConfig& defaultValue)
{
    MediaConfig result;

    std::string defaultPoster = ParseUtil::GetString(json, AdaptiveCardSchemaKey::DefaultPoster);
    result.defaultPoster = defaultPoster == "" ? defaultValue.defaultPoster : defaultPoster;

    std::string playButton = ParseUtil::GetString(json, AdaptiveCardSchemaKey::PlayButton);
    result.playButton = playButton == "" ? defaultValue.playButton : playButton;

    result.allowInlinePlayback =
        ParseUtil::GetBool(json, AdaptiveCardSchemaKey::AllowInlinePlayback, defaultValue.allowInlinePlayback);

    return result;
}

FontTypeDefinition HostConfig::GetFontType(FontType type) const
{
    switch (type)
    {
    case FontType::Monospace:
        return _fontTypes.monospaceFontType;
    case FontType::Default:
    default:
        return _fontTypes.defaultFontType;
    }
}

unsigned int FontSizesConfig::GetFontSize(TextSize size) const
{
    switch (size)
    {
    case TextSize::Small:
        return _small;
    case TextSize::Medium:
        return _medium;
    case TextSize::Large:
        return _large;
    case TextSize::ExtraLarge:
        return _extraLarge;
    case TextSize::Default:
    default:
        return _default;
    }
}

void FontSizesConfig::SetFontSize(TextSize size, unsigned int value)
{
    switch (size)
    {
    case TextSize::Small:
        _small = value;
    case TextSize::Medium:
        _medium = value;
    case TextSize::Large:
        _large = value;
    case TextSize::ExtraLarge:
        _extraLarge = value;
    case TextSize::Default:
    default:
        _default = value;
    }
}

unsigned int FontSizesConfig::GetDefaultFontSize(TextSize size)
{
    switch (size)
    {
    case TextSize::Small:
        return 10;
    case TextSize::Medium:
        return 14;
    case TextSize::Large:
        return 17;
    case TextSize::ExtraLarge:
        return 20;
    case TextSize::Default:
    default:
        return 12;
    }
}

unsigned int FontWeightsConfig::GetFontWeight(TextWeight weight) const
{
    switch (weight)
    {
    case TextWeight::Lighter:
        return _lighter;
    case TextWeight::Bolder:
        return _bolder;
    case TextWeight::Default:
    default:
        return _default;
    }
}

void FontWeightsConfig::SetFontWeight(TextWeight weight, unsigned int value)
{
    switch (weight)
    {
    case TextWeight::Lighter:
        _lighter = value;
    case TextWeight::Bolder:
        _bolder = value;
    case TextWeight::Default:
    default:
        _default = value;
    }
}

unsigned int FontWeightsConfig::GetDefaultFontWeight(TextWeight weight)
{
    switch (weight)
    {
    case AdaptiveCards::TextWeight::Lighter:
        return 200;
    case AdaptiveCards::TextWeight::Bolder:
        return 800;
    case AdaptiveCards::TextWeight::Default:
    default:
        return 400;
    }
}

std::string HostConfig::GetFontFamily(FontType fontType) const
{
    // desired font family
    auto fontFamilyValue = GetFontType(fontType).fontFamily;

    if (fontFamilyValue.empty())
    {
        if (fontType == FontType::Monospace)
        {
            // pass empty string for renderer to handle appropriate const default font family for Monospace
            fontFamilyValue = "";
        }
        else
        {
            // deprecated font family
            fontFamilyValue = _fontFamily;
            if (fontFamilyValue.empty())
            {
                // pass empty string for renderer to handle appropriate const default font family
                fontFamilyValue = "";
            }
        }
    }
    return fontFamilyValue;
}

unsigned int HostConfig::GetFontSize(FontType fontType, TextSize size) const
{
    // desired font size
    auto result = GetFontType(fontType).fontSizes.GetFontSize(size);

    // UINT_MAX used to check if value was defined
    if (result == UINT_MAX)
    {
        // default font size
        result = _fontTypes.defaultFontType.fontSizes.GetFontSize(size);
        if (result == UINT_MAX)
        {
            // deprecated font size
            result = _fontSizes.GetFontSize(size);
            if (result == UINT_MAX)
            {
                // constant default font size
                result = FontSizesConfig::GetDefaultFontSize(size);
            }
        }
    }
    return result;
}

unsigned int HostConfig::GetFontWeight(FontType fontType, TextWeight weight) const
{
    // desired font weight
    auto result = GetFontType(fontType).fontWeights.GetFontWeight(weight);

    // UINT_MAX used to check if value was defined
    if (result == UINT_MAX)
    {
        // default font weight
        result = _fontTypes.defaultFontType.fontWeights.GetFontWeight(weight);
        if (result == UINT_MAX)
        {
            // deprecated font weight
            result = _fontWeights.GetFontWeight(weight);
            if (result == UINT_MAX)
            {
                // constant default font weight
                result = FontWeightsConfig::GetDefaultFontWeight(weight);
            }
        }
    }
    return result;
}

const ContainerStyleDefinition& HostConfig::GetContainerStyle(ContainerStyle style) const
{
    switch (style)
    {
    case ContainerStyle::Accent:
        return _containerStyles.accentPalette;
    case ContainerStyle::Attention:
        return _containerStyles.attentionPalette;
    case ContainerStyle::Emphasis:
        return _containerStyles.emphasisPalette;
    case ContainerStyle::Good:
        return _containerStyles.goodPalette;
    case ContainerStyle::Warning:
        return _containerStyles.warningPalette;
    case ContainerStyle::Default:
    default:
        return _containerStyles.defaultPalette;
    }
}

std::string HostConfig::GetBackgroundColor(ContainerStyle style) const
{
    return GetContainerStyle(style).backgroundColor;
}

template<typename T> std::string GetColorFromColorConfig(T colorConfig, bool isSubtle)
{
    return (isSubtle) ? (colorConfig.subtleColor) : (colorConfig.defaultColor);
}

const ColorConfig& HostConfig::GetContainerColorConfig(const ColorsConfig& colors, ForegroundColor color) const
{
    switch (color)
    {
    case ForegroundColor::Accent:
        return colors.accent;
    case ForegroundColor::Attention:
        return colors.attention;
    case ForegroundColor::Dark:
        return colors.dark;
    case ForegroundColor::Good:
        return colors.good;
    case ForegroundColor::Light:
        return colors.light;
    case ForegroundColor::Warning:
        return colors.warning;
    case ForegroundColor::Default:
    default:
        return colors.defaultColor;
    }
}

std::string HostConfig::GetForegroundColor(ContainerStyle style, ForegroundColor color, bool isSubtle) const
{
    auto colorConfig = GetContainerColorConfig(GetContainerStyle(style).foregroundColors, color);
    return GetColorFromColorConfig(colorConfig, isSubtle);
}

std::string HostConfig::GetHighlightColor(ContainerStyle style, ForegroundColor color, bool isSubtle) const
{
    auto colorConfig = GetContainerColorConfig(GetContainerStyle(style).foregroundColors, color).highlightColors;
    return GetColorFromColorConfig(colorConfig, isSubtle);
}

std::string HostConfig::GetBorderColor(ContainerStyle style) const
{
    return GetContainerStyle(style).borderColor;
}

unsigned int HostConfig::GetBorderThickness(ContainerStyle style) const
{
    return GetContainerStyle(style).borderThickness;
}

std::string HostConfig::GetFontFamily() const
{
    return _fontFamily;
}

void HostConfig::SetFontFamily(const std::string& value)
{
    _fontFamily = value;
}

FontSizesConfig HostConfig::GetFontSizes() const
{
    return _fontSizes;
}

void HostConfig::SetFontSizes(const FontSizesConfig value)
{
    _fontSizes = value;
}

FontWeightsConfig HostConfig::GetFontWeights() const
{
    return _fontWeights;
}

void HostConfig::SetFontWeights(const FontWeightsConfig value)
{
    _fontWeights = value;
}

FontTypesDefinition HostConfig::GetFontTypes() const
{
    return _fontTypes;
}

void HostConfig::SetFontTypes(const FontTypesDefinition value)
{
    _fontTypes = value;
}

bool HostConfig::GetSupportsInteractivity() const
{
    return _supportsInteractivity;
}

void HostConfig::SetSupportsInteractivity(const bool value)
{
    _supportsInteractivity = value;
}

std::string HostConfig::GetImageBaseUrl() const
{
    return _imageBaseUrl;
}

void HostConfig::SetImageBaseUrl(const std::string& value)
{
    _imageBaseUrl = value;
}

ImageSizesConfig HostConfig::GetImageSizes() const
{
    return _imageSizes;
}

void HostConfig::SetImageSizes(const ImageSizesConfig value)
{
    _imageSizes = value;
}

ImageConfig HostConfig::GetImage() const
{
    return _image;
}

void HostConfig::SetImage(const ImageConfig value)
{
    _image = value;
}

SeparatorConfig HostConfig::GetSeparator() const
{
    return _separator;
}

void HostConfig::SetSeparator(const SeparatorConfig value)
{
    _separator = value;
}

SpacingConfig HostConfig::GetSpacing() const
{
    return _spacing;
}

void HostConfig::SetSpacing(const SpacingConfig value)
{
    _spacing = value;
}

AdaptiveCardConfig HostConfig::GetAdaptiveCard() const
{
    return _adaptiveCard;
}

void HostConfig::SetAdaptiveCard(const AdaptiveCardConfig value)
{
    _adaptiveCard = value;
}

ImageSetConfig HostConfig::GetImageSet() const
{
    return _imageSet;
}

void HostConfig::SetImageSet(const ImageSetConfig value)
{
    _imageSet = value;
}

FactSetConfig HostConfig::GetFactSet() const
{
    return _factSet;
}

void HostConfig::SetFactSet(const FactSetConfig value)
{
    _factSet = value;
}

ActionsConfig HostConfig::GetActions() const
{
    return _actions;
}

void HostConfig::SetActions(const ActionsConfig value)
{
    _actions = value;
}

ContainerStylesDefinition HostConfig::GetContainerStyles() const
{
    return _containerStyles;
}

void HostConfig::SetContainerStyles(const ContainerStylesDefinition value)
{
    _containerStyles = value;
}

MediaConfig HostConfig::GetMedia() const
{
    return _media;
}

void HostConfig::SetMedia(const MediaConfig value)
{
    _media = value;
}

InputsConfig HostConfig::GetInputs() const
{
    return _inputs;
}

void HostConfig::SetInputs(const InputsConfig value)
{
    _inputs = value;
}


/*
InputLabelsConfig HostConfig::GetInputLabels() const
{
    return _inputLabels;
}

void HostConfig::SetInputLabels(const InputLabelsConfig value)
{
    _inputLabels = value;
}

ErrorMessageConfig HostConfig::GetErrorMessage() const
{
    return _errorMessage;
}


void HostConfig::SetErrorMessage(const ErrorMessageConfig value)
{
    _errorMessage = value;
}
*/
