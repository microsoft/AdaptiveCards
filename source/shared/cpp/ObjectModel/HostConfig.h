#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"

namespace AdaptiveCards
{

struct FontSizesConfig
{
    unsigned int smallFontSize = 10;
    unsigned int defaultFontSize = 12;
    unsigned int mediumFontSize = 14;
    unsigned int largeFontSize = 17;
    unsigned int extraLargeFontSize = 20;

    static FontSizesConfig Deserialize(const Json::Value& json, const FontSizesConfig& defaultValue);
};

struct FontWeightsConfig
{
    unsigned int lighterWeight = 200;
    unsigned int defaultWeight = 400;
    unsigned int bolderWeight = 800;

    static FontWeightsConfig Deserialize(const Json::Value& json, const FontWeightsConfig& defaultValue);
};

struct ColorConfig
{
    std::string defaultColor;
    std::string subtleColor;

    static ColorConfig Deserialize(const Json::Value& json, const ColorConfig& defaultValue);
};

struct ColorsConfig
{
    ColorConfig defaultColor = { "#FF000000", "#B2000000" };
    ColorConfig accent = { "#FF0000FF", "#B20000FF" };
    ColorConfig dark = { "#FF101010", "#B2101010" };
    ColorConfig light = { "#FFFFFFFF", "#B2FFFFFF" };
    ColorConfig good = { "#FF008000", "#B2008000" };
    ColorConfig warning = { "#FFFFD700", "#B2FFD700" };
    ColorConfig attention = { "#FF8B0000", "#B28B0000" };

    static ColorsConfig Deserialize(const Json::Value& json, const ColorsConfig& defaultValue);
};

struct TextConfig
{
    TextWeight weight = TextWeight::Default;
    TextSize size = TextSize::Default;
    ForegroundColor color = ForegroundColor::Default;
    bool isSubtle = false;
    bool wrap = true;
    unsigned int maxWidth = 150;

    static TextConfig Deserialize(const Json::Value& json, const TextConfig& defaultValue);
};

struct SpacingConfig
{
    unsigned int smallSpacing = 3;
    unsigned int defaultSpacing = 8;
    unsigned int mediumSpacing = 20;
    unsigned int largeSpacing = 30;
    unsigned int extraLargeSpacing = 40;
    unsigned int paddingSpacing = 20;

    static SpacingConfig Deserialize(const Json::Value& json, const SpacingConfig& defaultValue);
};

struct SeparatorConfig
{
    unsigned int lineThickness = 1;
    std::string lineColor = "#B2000000";

    static SeparatorConfig Deserialize(const Json::Value& json, const SeparatorConfig& defaultValue);
};

struct ImageSizesConfig
{
    unsigned int smallSize = 80;
    unsigned int mediumSize = 120;
    unsigned int largeSize = 180;

    static ImageSizesConfig Deserialize(const Json::Value& json, const ImageSizesConfig& defaultValue);
};

struct ImageSetConfig
{
    ImageSize imageSize = ImageSize::Auto;
    unsigned int maxImageHeight = 100;

    static ImageSetConfig Deserialize(const Json::Value& json, const ImageSetConfig& defaultValue);
};

struct ImageConfig
{
    ImageSize imageSize = ImageSize::Auto;

    static ImageConfig Deserialize(const Json::Value& json, const ImageConfig& defaultValue);
};

struct AdaptiveCardConfig
{
    bool allowCustomStyle = true;

    static AdaptiveCardConfig Deserialize(const Json::Value& json, const AdaptiveCardConfig& defaultValue);
};

struct FactSetConfig
{
    TextConfig title = { TextWeight::Bolder };
    TextConfig value;
    unsigned int spacing = 10;

    static FactSetConfig Deserialize(const Json::Value& json, const FactSetConfig& defaultValue);
};

struct ContainerStyleDefinition
{
    std::string backgroundColor = "#FFFFFFFF";
    std::string borderColor = "#FF7F7F7F7F"; // CAUTION: Experimental feature for iOS. Not in v1 schema, subject to change.
    unsigned int borderThickness = 0; // CAUTION: Experimental feature for iOS. Not in v1 schema, subject to change.
    ColorsConfig foregroundColors;

    static ContainerStyleDefinition Deserialize(const Json::Value& json, const ContainerStyleDefinition& defaultValue);
};

struct ContainerStylesDefinition
{
    ContainerStyleDefinition defaultPalette;
    ContainerStyleDefinition emphasisPalette = 
    { "#08000000", "#08000000", 0,
        {
            { "#FF000000", "#B2000000" },   //defaultColor
            { "#FF0000FF", "#B20000FF" },   //accent
            { "#FF101010", "#B2101010" },   //dark
            { "#FFFFFFFF", "#B2FFFFFF" },   //light
            { "#FF008000", "#B2008000" },   //good
            { "#FFFFD700", "#B2FFD700" },   //warning
            { "#FF8B0000", "#B28B0000" }    //attention
        }
    };

    static ContainerStylesDefinition Deserialize(const Json::Value& json, const ContainerStylesDefinition& defaultValue);
};

struct ShowCardActionConfig
{
    ActionMode actionMode = ActionMode::Inline;
    ContainerStyle style = ContainerStyle::Emphasis;
    unsigned int inlineTopMargin = 16;

    static ShowCardActionConfig Deserialize(const Json::Value& json, const ShowCardActionConfig& defaultValue);
};

struct ActionsConfig
{
    ShowCardActionConfig showCard;
    ActionsOrientation actionsOrientation = ActionsOrientation::Horizontal;
    ActionAlignment actionAlignment = ActionAlignment::Stretch;
    unsigned int buttonSpacing = 10;
    unsigned int maxActions = 5;
    Spacing spacing = Spacing::Default;
    IconPlacement iconPlacement = IconPlacement::AboveTitle;

    static ActionsConfig Deserialize(const Json::Value& json, const ActionsConfig& defaultValue);
};

struct HostConfig
{
    std::string fontFamily = "Calibri";
    FontSizesConfig fontSizes;
    FontWeightsConfig fontWeights;
    bool supportsInteractivity = true;
    ImageSizesConfig imageSizes;
    ImageConfig image;
    SeparatorConfig separator;
    SpacingConfig spacing;
    AdaptiveCardConfig adaptiveCard;
    ImageSetConfig imageSet;
    FactSetConfig factSet;
    ActionsConfig actions;
    ContainerStylesDefinition containerStyles;

    static HostConfig Deserialize(const Json::Value& json);
    static HostConfig DeserializeFromString(const std::string jsonString);
};
}
