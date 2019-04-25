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

    result._fontStyles = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontStylesDefinition>(
        json, AdaptiveCardSchemaKey::FontStyles, result._fontStyles, FontStylesDefinition::Deserialize);

    // If the base style definition is set, it serves as the default for all not-specified container styles. Update
    // _containerStyles based on the base style definition to update the defaults.
    result._containerStyles.SetBaseStyle(json);
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

FontStyleDefinition FontStyleDefinition::Deserialize(const Json::Value& json, const FontStyleDefinition& defaultValue)
{
    FontStyleDefinition result;

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

FontStylesDefinition FontStylesDefinition::Deserialize(const Json::Value& json, const FontStylesDefinition& defaultValue)
{
    FontStylesDefinition result;

    result.defaultStyle = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontStyleDefinition>(
        json, AdaptiveCardSchemaKey::Default, defaultValue.defaultStyle, FontStyleDefinition::Deserialize);
    result.monospaceStyle = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontStyleDefinition>(
        json, AdaptiveCardSchemaKey::Monospace, defaultValue.defaultStyle, FontStyleDefinition::Deserialize);
    return result;
}

ColorConfig ColorConfig::Deserialize(const Json::Value& json, const ColorConfig& defaultValue)
{
    ColorConfig result;
    std::string defaultColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Default);
    result.defaultColor = defaultColor == "" ? defaultValue.defaultColor : defaultColor;

    std::string subtleColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Subtle);
    result.subtleColor = subtleColor == "" ? defaultValue.subtleColor : subtleColor;

    return result;
}

void ColorConfig::SetBaseColor(const std::string& baseColor)
{
    defaultColor = baseColor;
    subtleColor = baseColor;
}

ColorConfig GetColorConfig(const Json::Value& json, AdaptiveCardSchemaKey key, const ColorConfig& defaultValue)
{
    const std::string stringResult = ParseUtil::TryGetString(json, key);
    if (!stringResult.empty())
    {
        // If the host sets the color config to a single string, use that string for both default and subtle
        ColorConfig result = {stringResult, stringResult};
        return result;
    }
    else
    {
        // If it's not a string, parse it as a ColorConfig
        return ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json, key, defaultValue, &ColorConfig::Deserialize);
    }
}

ColorsConfig ColorsConfig::Deserialize(const Json::Value& json, const ColorsConfig& defaultValue)
{
    ColorsConfig result;

    result.defaultColor = GetColorConfig(json, AdaptiveCardSchemaKey::Default, defaultValue.defaultColor);
    result.accent = GetColorConfig(json, AdaptiveCardSchemaKey::Accent, defaultValue.accent);
    result.dark = GetColorConfig(json, AdaptiveCardSchemaKey::Dark, defaultValue.dark);
    result.light = GetColorConfig(json, AdaptiveCardSchemaKey::Light, defaultValue.light);
    result.good = GetColorConfig(json, AdaptiveCardSchemaKey::Good, defaultValue.good);
    result.warning = GetColorConfig(json, AdaptiveCardSchemaKey::Warning, defaultValue.warning);
    result.attention = GetColorConfig(json, AdaptiveCardSchemaKey::Attention, defaultValue.attention);

    return result;
}

void ColorsConfig::SetBaseColor(const std::string& baseColor)
{
    defaultColor.SetBaseColor(baseColor);
    accent.SetBaseColor(baseColor);
    dark.SetBaseColor(baseColor);
    light.SetBaseColor(baseColor);
    good.SetBaseColor(baseColor);
    warning.SetBaseColor(baseColor);
    attention.SetBaseColor(baseColor);
}

TextConfig TextConfig::Deserialize(const Json::Value& json, const TextConfig& defaultValue)
{
    TextConfig result;
    result.weight = ParseUtil::GetEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::Weight, defaultValue.weight, TextWeightFromString);

    result.size = ParseUtil::GetEnumValue<TextSize>(json, AdaptiveCardSchemaKey::Size, defaultValue.size, TextSizeFromString);

    result.style = ParseUtil::GetEnumValue<FontStyle>(json, AdaptiveCardSchemaKey::FontStyle, defaultValue.style, FontStyleFromString);

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

    result.highlightColors = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorsConfig>(json,
                                                                                          AdaptiveCardSchemaKey::HighlightColors,
                                                                                          defaultValue.highlightColors,
                                                                                          ColorsConfig::Deserialize);

    return result;
}

void ContainerStyleDefinition::SetBaseStyle(const Json::Value& json)
{
    Json::Value baseContainterStyleJson =
        json.get(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::BaseContainerStyle), Json::Value());

    std::string baseBackgroundColor = ParseUtil::TryGetString(baseContainterStyleJson, AdaptiveCardSchemaKey::BackgroundColor);
    if (!baseBackgroundColor.empty())
    {
        backgroundColor = baseBackgroundColor;
    }

    std::string baseForegroundColor = ParseUtil::TryGetString(baseContainterStyleJson, AdaptiveCardSchemaKey::ForegroundColor);
    if (!baseForegroundColor.empty())
    {
        foregroundColors.SetBaseColor(baseForegroundColor);
    }

    std::string baseHighlightColor = ParseUtil::TryGetString(baseContainterStyleJson, AdaptiveCardSchemaKey::HighlightColor);
    if (!baseHighlightColor.empty())
    {
        highlightColors.SetBaseColor(baseHighlightColor);
    }
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

void ContainerStylesDefinition::SetBaseStyle(const Json::Value& json)
{
    defaultPalette.SetBaseStyle(json);
    emphasisPalette.SetBaseStyle(json);
    goodPalette.SetBaseStyle(json);
    attentionPalette.SetBaseStyle(json);
    warningPalette.SetBaseStyle(json);
    accentPalette.SetBaseStyle(json);
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

FontStyleDefinition HostConfig::GetFontStyle(FontStyle style) const
{
    switch (style)
    {
    case FontStyle::Monospace:
        return _fontStyles.monospaceStyle;
    case FontStyle::Default:
    default:
        return _fontStyles.defaultStyle;
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

std::string HostConfig::GetFontFamily(FontStyle style) const
{
    // desired font family
    auto fontFamilyValue = GetFontStyle(style).fontFamily;

    if (fontFamilyValue.empty())
    {
        if (style == FontStyle::Monospace)
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

unsigned int HostConfig::GetFontSize(FontStyle style, TextSize size) const
{
    // desired font size
    auto result = GetFontStyle(style).fontSizes.GetFontSize(size);

    // UINT_MAX used to check if value was defined
    if (result == UINT_MAX)
    {
        // default font size
        result = _fontStyles.defaultStyle.fontSizes.GetFontSize(size);
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

unsigned int HostConfig::GetFontWeight(FontStyle style, TextWeight weight) const
{
    // desired font weight
    auto result = GetFontStyle(style).fontWeights.GetFontWeight(weight);

    // UINT_MAX used to check if value was defined
    if (result == UINT_MAX)
    {
        // default font weight
        result = _fontStyles.defaultStyle.fontWeights.GetFontWeight(weight);
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

std::string HostConfig::GetContainerColor(const ColorsConfig& colors, ForegroundColor color, bool isSubtle) const
{
    switch (color)
    {
    case ForegroundColor::Accent:
        return (isSubtle) ? (colors.accent.subtleColor) : (colors.accent.defaultColor);
    case ForegroundColor::Attention:
        return (isSubtle) ? (colors.attention.subtleColor) : (colors.attention.defaultColor);
    case ForegroundColor::Dark:
        return (isSubtle) ? (colors.dark.subtleColor) : (colors.dark.defaultColor);
    case ForegroundColor::Good:
        return (isSubtle) ? (colors.good.subtleColor) : (colors.good.defaultColor);
    case ForegroundColor::Light:
        return (isSubtle) ? (colors.light.subtleColor) : (colors.light.defaultColor);
    case ForegroundColor::Warning:
        return (isSubtle) ? (colors.warning.subtleColor) : (colors.warning.defaultColor);
    case ForegroundColor::Default:
    default:
        return (isSubtle) ? (colors.defaultColor.subtleColor) : (colors.defaultColor.defaultColor);
    }
}

std::string HostConfig::GetForegroundColor(ContainerStyle style, ForegroundColor color, bool isSubtle) const
{
    auto foregroundColors = GetContainerStyle(style).foregroundColors;
    return GetContainerColor(foregroundColors, color, isSubtle);
}

std::string HostConfig::GetHighlightColor(ContainerStyle style, ForegroundColor color, bool isSubtle) const
{
    auto highlightColors = GetContainerStyle(style).highlightColors;
    return GetContainerColor(highlightColors, color, isSubtle);
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

FontStylesDefinition HostConfig::GetFontStyles() const
{
    return _fontStyles;
}

void HostConfig::SetFontStyles(const FontStylesDefinition value)
{
    _fontStyles = value;
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
