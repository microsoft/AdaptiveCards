#include "pch.h"
#include "HostConfig.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

HostConfig HostConfig::DeserializeFromString(const std::string jsonString)
{
    return HostConfig::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

HostConfig HostConfig::Deserialize(const Json::Value& json)
{
    HostConfig result;
    std::string fontFamily = ParseUtil::GetString(json, AdaptiveCardSchemaKey::FontFamily);
    result.fontFamily = fontFamily == "" ? fontFamily : result.fontFamily;

    result.supportsInteractivity = ParseUtil::GetBool(
        json, AdaptiveCardSchemaKey::SupportsInteractivity, result.supportsInteractivity);

    result.fontSizes = ParseUtil::ExtractJsonValueAndMergeWithDefault<FontSizesConfig>(
        json, AdaptiveCardSchemaKey::FontSizes, result.fontSizes, FontSizesConfig::Deserialize);

    result.containerStyles = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStylesDefinition>(
        json, AdaptiveCardSchemaKey::ContainerStyles, result.containerStyles, ContainerStylesDefinition::Deserialize);
        
    result.imageSizes = ParseUtil::ExtractJsonValueAndMergeWithDefault<ImageSizesConfig>(
        json, AdaptiveCardSchemaKey::ImageSizes, result.imageSizes, ImageSizesConfig::Deserialize);

    result.spacing = ParseUtil::ExtractJsonValueAndMergeWithDefault<SpacingConfig>(
        json, AdaptiveCardSchemaKey::Spacing, result.spacing, SpacingConfig::Deserialize);

    result.adaptiveCard = ParseUtil::ExtractJsonValueAndMergeWithDefault<AdaptiveCardConfig>(
        json, AdaptiveCardSchemaKey::AdaptiveCard, result.adaptiveCard, AdaptiveCardConfig::Deserialize);

    result.actions = ParseUtil::ExtractJsonValueAndMergeWithDefault<ActionsConfig>(
        json, AdaptiveCardSchemaKey::Actions, result.actions, ActionsConfig::Deserialize);

    return result;
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

ColorConfig ColorConfig::Deserialize(const Json::Value& json, const ColorConfig& defaultValue)
{
    ColorConfig result;
    std::string defaultColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Default);
    result.defaultColor = defaultColor == "" ? defaultValue.defaultColor : defaultColor;

    std::string subtleColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Subtle);
    result.subtleColor = subtleColor == "" ? defaultValue.subtleColor: subtleColor;

    return result;
}

ColorsConfig ColorsConfig::Deserialize(const Json::Value& json, const ColorsConfig& defaultValue)
{
    ColorsConfig result;
    auto colorDeserializer = &ColorConfig::Deserialize;

    result.defaultColor = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(
        json, AdaptiveCardSchemaKey::Default, defaultValue.defaultColor, colorDeserializer);

    result.accent = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(
        json, AdaptiveCardSchemaKey::Accent, defaultValue.accent, colorDeserializer);

    result.dark = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(
        json, AdaptiveCardSchemaKey::Dark, defaultValue.dark, colorDeserializer);

    result.light = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(
        json, AdaptiveCardSchemaKey::Light, defaultValue.light, colorDeserializer);

    result.good = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(
        json, AdaptiveCardSchemaKey::Good, defaultValue.good, colorDeserializer);

    result.warning = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(
        json, AdaptiveCardSchemaKey::Warning, defaultValue.warning, colorDeserializer);

    result.attention = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorConfig>(
        json, AdaptiveCardSchemaKey::Attention, defaultValue.attention, colorDeserializer);

    return result;
}

TextConfig TextConfig::Deserialize(const Json::Value& json, const TextConfig& defaultValue)
{
    TextConfig result;
    result.weight = ParseUtil::GetEnumValue<TextWeight>(
        json, AdaptiveCardSchemaKey::Weight, defaultValue.weight, TextWeightFromString);

    result.size = ParseUtil::GetEnumValue<TextSize>(
        json, AdaptiveCardSchemaKey::Size, defaultValue.size, TextSizeFromString);

    result.color = ParseUtil::GetEnumValue<ForegroundColor>(
        json, AdaptiveCardSchemaKey::Color, defaultValue.color, ForegroundColorFromString);

    result.isSubtle = ParseUtil::GetBool(
        json, AdaptiveCardSchemaKey::IsSubtle, defaultValue.isSubtle);

    result.wrap = ParseUtil::GetBool(
        json, AdaptiveCardSchemaKey::Wrap, defaultValue.wrap);

    result.maxWidth = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::MaxWidth, defaultValue.maxWidth);

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
    result.imageSize = ParseUtil::GetEnumValue<ImageSize>(
        json, AdaptiveCardSchemaKey::ImageSet, defaultValue.imageSize, ImageSizeFromString);

    result.maxImageHeight = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxImageHeight, defaultValue.maxImageHeight);

    return result;
}

FactSetConfig FactSetConfig::Deserialize(const Json::Value& json, const FactSetConfig& defaultValue)
{
    FactSetConfig result;

    result.spacing = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Spacing, defaultValue.spacing);
    result.title = ParseUtil::ExtractJsonValueAndMergeWithDefault<TextConfig>(
        json, AdaptiveCardSchemaKey::Title, defaultValue.title, TextConfig::Deserialize);

    result.value = ParseUtil::ExtractJsonValueAndMergeWithDefault<TextConfig>(
        json, AdaptiveCardSchemaKey::Value, defaultValue.value, TextConfig::Deserialize);

    return result;
}

ShowCardActionConfig ShowCardActionConfig::Deserialize(const Json::Value&json, const ShowCardActionConfig& defaultValue)
{
    ShowCardActionConfig result;
    result.actionMode = ParseUtil::GetEnumValue<ActionMode>(
        json, AdaptiveCardSchemaKey::ActionMode, defaultValue.actionMode, ActionModeFromString);
    result.inlineTopMargin = ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::InlineTopMargin, defaultValue.inlineTopMargin);
    result.style = ParseUtil::GetEnumValue<ContainerStyle>(
        json, AdaptiveCardSchemaKey::Style, defaultValue.style, ContainerStyleFromString);

    return result;
}

ActionsConfig ActionsConfig::Deserialize(const Json::Value& json, const ActionsConfig& defaultValue)
{
    ActionsConfig result;

    result.actionsOrientation = ParseUtil::GetEnumValue<ActionsOrientation>(
        json, AdaptiveCardSchemaKey::ActionsOrientation, defaultValue.actionsOrientation, ActionsOrientationFromString);

    result.actionAlignment = ParseUtil::GetEnumValue<ActionAlignment>(
        json, AdaptiveCardSchemaKey::ActionAlignment, defaultValue.actionAlignment, ActionAlignmentFromString);

    result.buttonSpacing = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::ButtonSpacing, defaultValue.buttonSpacing);

    result.maxActions = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::MaxActions, defaultValue.maxActions);

    result.showCard = ParseUtil::ExtractJsonValueAndMergeWithDefault<ShowCardActionConfig>(
        json, AdaptiveCardSchemaKey::ShowCard, defaultValue.showCard, ShowCardActionConfig::Deserialize);

    return result;
}

SpacingConfig AdaptiveCards::SpacingConfig::Deserialize(const Json::Value & json, const SpacingConfig & defaultValue)
{
    SpacingConfig result;

    result.smallSpacing = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::Small, defaultValue.smallSpacing);

    result.defaultSpacing = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::Default, defaultValue.defaultSpacing);

    result.mediumSpacing = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::Medium, defaultValue.mediumSpacing);

    result.largeSpacing = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::Large, defaultValue.largeSpacing);

    result.extraLargeSpacing = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::ExtraLarge, defaultValue.extraLargeSpacing);

    result.paddingSpacing = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::Padding, defaultValue.paddingSpacing);

    return result;
}

SeparatorConfig AdaptiveCards::SeparatorConfig::Deserialize(const Json::Value & json, const SeparatorConfig & defaultValue)
{
    SeparatorConfig result;

    result.lineThickness = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::LineThickness, defaultValue.lineThickness);

    std::string lineColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::LineColor);
    result.lineColor = lineColor == "" ? defaultValue.lineColor : lineColor;

    return result;
}

ContainerStyleDefinition AdaptiveCards::ContainerStyleDefinition::Deserialize(const Json::Value & json, const ContainerStyleDefinition & defaultValue)
{
    ContainerStyleDefinition result;

    std::string backgroundColor = ParseUtil::GetString(json, AdaptiveCardSchemaKey::BackgroundColor);
    result.backgroundColor = backgroundColor == "" ? defaultValue.backgroundColor : backgroundColor;

    result.foregroundColors = ParseUtil::ExtractJsonValueAndMergeWithDefault<ColorsConfig>(
        json, AdaptiveCardSchemaKey::ForegroundColors, defaultValue.foregroundColors, ColorsConfig::Deserialize);

    return result;
}

ContainerStylesDefinition AdaptiveCards::ContainerStylesDefinition::Deserialize(const Json::Value & json, const ContainerStylesDefinition & defaultValue)
{
    ContainerStylesDefinition result;

    result.defaultPalette = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStyleDefinition>(
        json, AdaptiveCardSchemaKey::Default, defaultValue.defaultPalette, ContainerStyleDefinition::Deserialize);

    result.emphasisPalette = ParseUtil::ExtractJsonValueAndMergeWithDefault<ContainerStyleDefinition>(
        json, AdaptiveCardSchemaKey::Emphasis, defaultValue.emphasisPalette, ContainerStyleDefinition::Deserialize);

    return result;
}

FontWeightsConfig AdaptiveCards::FontWeightsConfig::Deserialize(const Json::Value & json, const FontWeightsConfig & defaultValue)
{
    FontWeightsConfig result;

    result.lighterWeight = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::Lighter, defaultValue.lighterWeight);

    result.defaultWeight = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::Default, defaultValue.defaultWeight);

    result.bolderWeight = ParseUtil::GetUInt(
        json, AdaptiveCardSchemaKey::Bolder, defaultValue.bolderWeight);

    return result;
}

ImageConfig AdaptiveCards::ImageConfig::Deserialize(const Json::Value & json, const ImageConfig & defaultValue)
{
    ImageConfig result;

    result.imageSize = ParseUtil::GetEnumValue<ImageSize>(
        json, AdaptiveCardSchemaKey::ImageSize, defaultValue.imageSize, ImageSizeFromString);

    return result;
}
