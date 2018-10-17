#include "pch.h"
#include "HostConfig.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

HostConfig HostConfig::DeserializeFromString(const std::string jsonString)
{
    return HostConfig::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

HostConfig::HostConfig()
{
    fontSizes = FontSizesConfig();
    fontWeights = FontWeightsConfig();
}

HostConfig HostConfig::Deserialize(const Json::Value& json)
{
    HostConfig result;
    std::string fontFamily = ParseUtil::GetString(json, AdaptiveCardSchemaKey::FontFamily);
    result.fontFamily = fontFamily != "" ? fontFamily : result.fontFamily;

    result.supportsInteractivity =
        ParseUtil::GetBool(json, AdaptiveCardSchemaKey::SupportsInteractivity, result.supportsInteractivity);

    result.imageBaseUrl = ParseUtil::GetString(json, AdaptiveCardSchemaKey::ImageBaseUrl);

    result.factSet = ParseUtil::ExtractJsonValueAndMergeWithDefault<FactSetConfig>(json,
                                                                                   AdaptiveCardSchemaKey::FactSet,
                                                                                   result.factSet,
                                                                                   FactSetConfig::Deserialize);

    result.fontSizes = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontSizesConfig>(json,
                                                                                       AdaptiveCardSchemaKey::FontSizes,
                                                                                       result.fontSizes,
                                                                                       FontSizesConfig::Deserialize);

    result.fontWeights = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontWeightsConfig>(json,
                                                                                           AdaptiveCardSchemaKey::FontWeights,
                                                                                           result.fontWeights,
                                                                                           FontWeightsConfig::Deserialize);

    result.fontStyles = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontStylesDefinition>(
        json, AdaptiveCardSchemaKey::FontStyles, result.fontStyles, FontStylesDefinition::Deserialize);

    result.containerStyles = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStylesDefinition>(
        json, AdaptiveCardSchemaKey::ContainerStyles, result.containerStyles, ContainerStylesDefinition::Deserialize);

    result.image =
        ParseUtil::ExtractJsonValueAndMergeWithDefault<ImageConfig>(json, AdaptiveCardSchemaKey::Image, result.image, ImageConfig::Deserialize);

    result.imageSet = ParseUtil::ExtractJsonValueAndMergeWithDefault<ImageSetConfig>(json,
                                                                                     AdaptiveCardSchemaKey::ImageSet,
                                                                                     result.imageSet,
                                                                                     ImageSetConfig::Deserialize);

    result.imageSizes = ParseUtil::ExtractJsonValueAndMergeWithDefault<ImageSizesConfig>(json,
                                                                                         AdaptiveCardSchemaKey::ImageSizes,
                                                                                         result.imageSizes,
                                                                                         ImageSizesConfig::Deserialize);

    result.separator = ParseUtil::ExtractJsonValueAndMergeWithDefault<SeparatorConfig>(json,
                                                                                       AdaptiveCardSchemaKey::Separator,
                                                                                       result.separator,
                                                                                       SeparatorConfig::Deserialize);

    result.spacing = ParseUtil::ExtractJsonValueAndMergeWithDefault<SpacingConfig>(json,
                                                                                   AdaptiveCardSchemaKey::Spacing,
                                                                                   result.spacing,
                                                                                   SpacingConfig::Deserialize);

    result.adaptiveCard = ParseUtil::ExtractJsonValueAndMergeWithDefault<AdaptiveCardConfig>(
        json, AdaptiveCardSchemaKey::AdaptiveCard, result.adaptiveCard, AdaptiveCardConfig::Deserialize);

    result.actions = ParseUtil::ExtractJsonValueAndMergeWithDefault<ActionsConfig>(json,
                                                                                   AdaptiveCardSchemaKey::Actions,
                                                                                   result.actions,
                                                                                   ActionsConfig::Deserialize);

    result.media =
        ParseUtil::ExtractJsonValueAndMergeWithDefault<MediaConfig>(json, AdaptiveCardSchemaKey::Media, result.media, MediaConfig::Deserialize);

    return result;
}

FontSizesConfig::FontSizesConfig()
{
    smallFontSize = UINT_MAX;
    defaultFontSize = UINT_MAX;
    mediumFontSize = UINT_MAX;
    largeFontSize = UINT_MAX;
    extraLargeFontSize = UINT_MAX;
}

FontSizesConfig::FontSizesConfig(unsigned int s, unsigned int d, unsigned int m, unsigned int l, unsigned int xl)
{
    smallFontSize = s;
    defaultFontSize = d;
    mediumFontSize = m;
    largeFontSize = l;
    extraLargeFontSize = xl;
}

FontSizesConfig FontSizesConfig::Deserialize(const Json::Value& json, const FontSizesConfig& defaultValue)
{
    FontSizesConfig result;
    result.smallFontSize = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Small, defaultValue.smallFontSize);
    result.defaultFontSize = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Default, defaultValue.defaultFontSize);
    result.mediumFontSize = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Medium, defaultValue.mediumFontSize);
    result.largeFontSize = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Large, defaultValue.largeFontSize);
    result.extraLargeFontSize = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::ExtraLarge, defaultValue.extraLargeFontSize);
    return result;
}

FontStyleDefinition FontStyleDefinition::Deserialize(const Json::Value& json, const FontStyleDefinition& defaultValue)
{
    FontStyleDefinition result;

    const std::string fontFamily = ParseUtil::GetString(json, AdaptiveCardSchemaKey::FontFamily);
    result.fontFamily = fontFamily == "" ? defaultValue.fontFamily : fontFamily;

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

    result.defaultStyle = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontStyleDefinition>(json,
                                                                                         AdaptiveCardSchemaKey::Default, defaultValue.defaultStyle,
                                                                                         FontStyleDefinition::Deserialize);
    result.displayStyle = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontStyleDefinition>(json,
                                                                                         AdaptiveCardSchemaKey::Display, defaultValue.defaultStyle,
                                                                                         FontStyleDefinition::Deserialize);
    result.monospaceStyle = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontStyleDefinition>(json,
                                                                                         AdaptiveCardSchemaKey::Monospace, defaultValue.defaultStyle,
                                                                                         FontStyleDefinition::Deserialize);
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

ColorsConfig ColorsConfig::Deserialize(const Json::Value& json, const ColorsConfig& defaultValue)
{
    ColorsConfig result;
    auto colorDeserializer = &ColorConfig::Deserialize;

    result.defaultColor = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json,
                                                                                      AdaptiveCardSchemaKey::Default,
                                                                                      defaultValue.defaultColor,
                                                                                      colorDeserializer);

    result.accent =
        ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json, AdaptiveCardSchemaKey::Accent, defaultValue.accent, colorDeserializer);

    result.dark =
        ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json, AdaptiveCardSchemaKey::Dark, defaultValue.dark, colorDeserializer);

    result.light =
        ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json, AdaptiveCardSchemaKey::Light, defaultValue.light, colorDeserializer);

    result.good =
        ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json, AdaptiveCardSchemaKey::Good, defaultValue.good, colorDeserializer);

    result.warning =
        ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json, AdaptiveCardSchemaKey::Warning, defaultValue.warning, colorDeserializer);

    result.attention = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(json,
                                                                                   AdaptiveCardSchemaKey::Attention,
                                                                                   defaultValue.attention,
                                                                                   colorDeserializer);

    return result;
}

TextConfig TextConfig::Deserialize(const Json::Value& json, const TextConfig& defaultValue)
{
    TextConfig result;
    result.weight = ParseUtil::GetEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::Weight, defaultValue.weight, TextWeightFromString);

    result.size = ParseUtil::GetEnumValue<TextSize>(json, AdaptiveCardSchemaKey::Size, defaultValue.size, TextSizeFromString);

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

    return result;
}

ContainerStylesDefinition ContainerStylesDefinition::Deserialize(const Json::Value& json, const ContainerStylesDefinition& defaultValue)
{
    ContainerStylesDefinition result;

    result.defaultPalette = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStyleDefinition>(
        json, AdaptiveCardSchemaKey::Default, defaultValue.defaultPalette, ContainerStyleDefinition::Deserialize);

    result.emphasisPalette = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStyleDefinition>(
        json, AdaptiveCardSchemaKey::Emphasis, defaultValue.emphasisPalette, ContainerStyleDefinition::Deserialize);

    return result;
}

FontWeightsConfig::FontWeightsConfig()
{
    lighterWeight = UINT_MAX;
    defaultWeight = UINT_MAX;
    bolderWeight = UINT_MAX;
}

FontWeightsConfig::FontWeightsConfig(unsigned int l, unsigned int d, unsigned int b)
{
    lighterWeight = l;
    defaultWeight = d;
    bolderWeight = b;
}

FontWeightsConfig FontWeightsConfig::Deserialize(const Json::Value& json, const FontWeightsConfig& defaultValue)
{
    FontWeightsConfig result;

    result.lighterWeight = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Lighter, defaultValue.lighterWeight);

    result.defaultWeight = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Default, defaultValue.defaultWeight);

    result.bolderWeight = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Bolder, defaultValue.bolderWeight);

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

FontStyleDefinition HostConfig::GetFontStyle(FontStyle style)
{
    switch (style)
    {
    case FontStyle::Display:
        return fontStyles.displayStyle;
    case FontStyle::Monospace:
        return fontStyles.monospaceStyle;
    case FontStyle::Default:
    default:
        return fontStyles.defaultStyle;
    }
}

unsigned int FontSizesConfig::GetFontSize(TextSize size)
{
    switch (size)
    {
    case TextSize::Small:
        return smallFontSize;
    case TextSize::Medium:
        return mediumFontSize;
    case TextSize::Large:
        return largeFontSize;
    case TextSize::ExtraLarge:
        return extraLargeFontSize;
    case TextSize::Default:
    default:
        return defaultFontSize;
    }
}

void FontSizesConfig::SetFontSize(TextSize size, unsigned int value)
{
    switch (size)
    {
    case TextSize::Small:
        smallFontSize = value;
    case TextSize::Medium:
        mediumFontSize = value;
    case TextSize::Large:
        largeFontSize = value;
    case TextSize::ExtraLarge:
        extraLargeFontSize = value;
    case TextSize::Default:
    default:
        defaultFontSize = value;
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

unsigned int FontWeightsConfig::GetFontWeight(TextWeight weight)
{
    switch (weight)
    {
    case TextWeight::Lighter:
        return lighterWeight;
    case TextWeight::Bolder:
        return bolderWeight;
    case TextWeight::Default:
    default:
        return defaultWeight;
    }
}

void FontWeightsConfig::SetFontWeight(TextWeight weight, unsigned int value)
{
    switch (weight)
    {
    case TextWeight::Lighter:
        lighterWeight = value;
    case TextWeight::Bolder:
        bolderWeight = value;
    case TextWeight::Default:
    default:
        defaultWeight = value;
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

std::string HostConfig::getFontFamily(FontStyle style)
{
    // desired font family
    auto fontFamilyValue = GetFontStyle(style).fontFamily;

    if (fontFamilyValue.empty())
    {
        // default font family
        fontFamilyValue = fontStyles.defaultStyle.fontFamily;
        if (fontFamilyValue.empty())
        {
            // deprecated font family
            fontFamilyValue = fontFamily;
            if (fontFamilyValue.empty())
            {
                // pass empty string for renderer to handle appropriate const default font family
                fontFamilyValue = "";
            }
        }
    }
    return fontFamilyValue;
}

unsigned int HostConfig::getFontSize(FontStyle style, TextSize size)
{
    // desired font size
    auto result = GetFontStyle(style).fontSizes.GetFontSize(size);

    // UINT_MAX used to check if value was defined
    if (result == UINT_MAX)
    {
        // default font size
        result = fontStyles.defaultStyle.fontSizes.GetFontSize(size);
        if (result == UINT_MAX)
        {
            // deprecated font size
            result = fontSizes.GetFontSize(size);
            if (result == UINT_MAX)
            {
                // constant default font size
                result = FontSizesConfig::GetDefaultFontSize(size);
            }
        }
    }
    return result;
}

unsigned int HostConfig::getFontWeight(FontStyle style, TextWeight weight)
{
    // desired font weight
    auto result = GetFontStyle(style).fontWeights.GetFontWeight(weight);

    // UINT_MAX used to check if value was defined
    if (result == UINT_MAX)
    {
        // default font weight
        result = fontStyles.defaultStyle.fontWeights.GetFontWeight(weight);
        if (result == UINT_MAX)
        {
            // deprecated font weight
            result = fontWeights.GetFontWeight(weight);
            if (result == UINT_MAX)
            {
                // constant default font weight
                result = FontWeightsConfig::GetDefaultFontWeight(weight);
            }
        }
    }
    return result;
}

std::string HostConfig::GetFontFamily() const
{
    return fontFamily;
}

void HostConfig::SetFontFamily(const std::string& value)
{
    fontFamily = value;
}

FontSizesConfig HostConfig::GetFontSizes() const
{
    return fontSizes;
}

void HostConfig::SetFontSizes(const FontSizesConfig value)
{
    fontSizes = value;
}

FontWeightsConfig HostConfig::GetFontWeights() const
{
    return fontWeights;
}

void HostConfig::SetFontWeights(const FontWeightsConfig value)
{
    fontWeights = value;
}

FontStylesDefinition HostConfig::GetFontStyles() const
{
    return fontStyles;
}

void HostConfig::SetFontStyles(const FontStylesDefinition value)
{
    fontStyles = value;
}

bool HostConfig::GetSupportsInteractivity() const
{
    return supportsInteractivity;
}

void HostConfig::SetSupportsInteractivity(const bool value)
{
    supportsInteractivity = value;
}

std::string HostConfig::GetImageBaseUrl() const
{
    return imageBaseUrl;
}

void HostConfig::SetImageBaseUrl(const std::string& value)
{
    imageBaseUrl = value;
}

ImageSizesConfig HostConfig::GetImageSizes() const
{
    return imageSizes;
}

void HostConfig::SetImageSizes(const ImageSizesConfig value)
{
    imageSizes = value;
}

ImageConfig HostConfig::GetImage() const
{
    return image;
}

void HostConfig::SetImage(const ImageConfig value)
{
    image = value;
}

SeparatorConfig HostConfig::GetSeparator() const
{
    return separator;
}

void HostConfig::SetSeparator(const SeparatorConfig value)
{
    separator = value;
}

SpacingConfig HostConfig::GetSpacing() const
{
    return spacing;
}

void HostConfig::SetSpacing(const SpacingConfig value)
{
    spacing = value;
}

AdaptiveCardConfig HostConfig::GetAdaptiveCard() const
{
    return adaptiveCard;
}

void HostConfig::SetAdaptiveCard(const AdaptiveCardConfig value)
{
    adaptiveCard = value;
}

ImageSetConfig HostConfig::GetImageSet() const
{
    return imageSet;
}

void HostConfig::SetImageSet(const ImageSetConfig value)
{
    imageSet = value;
}

FactSetConfig HostConfig::GetFactSet() const
{
    return factSet;
}

void HostConfig::SetFactSet(const FactSetConfig value)
{
    factSet = value;
}

ActionsConfig HostConfig::GetActions() const
{
    return actions;
}

void HostConfig::SetActions(const ActionsConfig value)
{
    actions = value;
}

ContainerStylesDefinition HostConfig::GetContainerStyles() const
{
    return containerStyles;
}

void HostConfig::SetContainerStyles(const ContainerStylesDefinition value)
{
    containerStyles = value;
}

MediaConfig HostConfig::GetMedia() const
{
    return media;
}

void HostConfig::SetMedia(const MediaConfig value)
{
    media = value;
}
