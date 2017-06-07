#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"

namespace AdaptiveCards
{
struct SpacingDefinition
{
    unsigned int left = 0;
    unsigned int right = 0;
    unsigned int top = 0;
    unsigned int bottom = 0;

    static SpacingDefinition Deserialize(const Json::Value& json, const SpacingDefinition& default);
};

struct FontSizesConfig
{
    unsigned int smallFontSize = 10;
    unsigned int normalFontSize = 12;
    unsigned int mediumFontSize = 14;
    unsigned int largeFontSize = 17;
    unsigned int extraLargeFontSize = 20;

    static FontSizesConfig Deserialize(const Json::Value& json, const FontSizesConfig& default);
};

struct ColorConfig
{
    std::string normal;
    std::string subtle;

    static ColorConfig Deserialize(const Json::Value& json, const ColorConfig& default);
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

    static ColorsConfig Deserialize(const Json::Value& json, const ColorsConfig& default);
};

struct TextConfig
{
    TextWeight weight = TextWeight::Normal;
    TextSize size = TextSize::Normal;
    TextColor color = TextColor::Default;
    bool isSubtle = false;

    static TextConfig Deserialize(const Json::Value& json, const TextConfig& default);
};

struct SeparationConfig
{
    unsigned int spacing = 10;
    unsigned int lineThickness = 0;
    std::string lineColor = "#FF101010";

    static SeparationConfig Deserialize(const Json::Value& json, const SeparationConfig& default);
};
struct ImageSizesConfig
{
    unsigned int smallSize = 80;
    unsigned int mediumSize = 120;
    unsigned int largeSize = 180;

    static ImageSizesConfig Deserialize(const Json::Value& json, const ImageSizesConfig& default);
};

struct TextBlockConfig
{
    SeparationConfig smallSeparation;
    SeparationConfig normalSeparation;
    SeparationConfig mediumSeparation;
    SeparationConfig largeSeparation;
    SeparationConfig extraLargeSeparation;

    static TextBlockConfig Deserialize(const Json::Value& json, const TextBlockConfig& default);
};

struct ImageSetConfig
{
    ImageSize imageSize = ImageSize::Medium;
    SeparationConfig separation;

    static ImageSetConfig Deserialize(const Json::Value& json, const ImageSetConfig& default);
};

struct ColumnConfig
{
    SeparationConfig separation;
    static ColumnConfig Deserialize(const Json::Value& json, const ColumnConfig& default);
};

struct ContainerStyleConfig
{
    std::string backgroundColor = "#00FFFFFF";
    std::string borderColor = "#00FFFFFF";
    SpacingDefinition borderThickness;
    SpacingDefinition padding;

    static ContainerStyleConfig Deserialize(const Json::Value& json, const ContainerStyleConfig& default);
};

struct ContainerConfig
{
    SeparationConfig separation;
    ContainerStyleConfig normal;
    ContainerStyleConfig emphasis = { "#FFEEEEEE", "#FFAAAAAA", SpacingDefinition{ 1, 1, 1, 1 }, SpacingDefinition{10, 10, 10, 10 } };

    static ContainerConfig Deserialize(const Json::Value& json, const ContainerConfig& default);
};

struct ColumnSetConfig
{
    SeparationConfig separation;

    static ColumnSetConfig Deserialize(const Json::Value& json, const ColumnSetConfig& default);
};

struct ImageConfig
{
    SeparationConfig separation;

    static ImageConfig Deserialize(const Json::Value& json, const ImageConfig& default);
};

struct AdaptiveCardConfig
{
    SpacingDefinition padding = { 8, 8, 8, 8 };
    std::string backgroundColor = "#FFFFFFFF";

    static AdaptiveCardConfig Deserialize(const Json::Value& json, const AdaptiveCardConfig& default);
};

struct FactSetConfig
{
    TextConfig title = { TextWeight::Bolder };
    TextConfig value;
    unsigned int spacing = 20;
    SeparationConfig separation;

    static FactSetConfig Deserialize(const Json::Value& json, const FactSetConfig& default);
};

struct ShowCardActionConfig
{
    ActionMode actionMode = ActionMode::InlineEdgeToEdge;
    std::string backgroundColor = "#FFF8F8F8";
    unsigned int inlineTopMargin = 16;
    SpacingDefinition padding = { 16, 16, 16, 16 };

    static ShowCardActionConfig Deserialize(const Json::Value& json, const ShowCardActionConfig& default);
};

struct ActionsConfig
{
    ShowCardActionConfig showCard;
    ActionsOrientation actionsOrientation = ActionsOrientation::Horizontal;
    ActionAlignment actionAlignment = ActionAlignment::Center;
    unsigned int buttonSpacing = 8;
    unsigned int maxActions = 5;
    SeparationConfig separation;

    static ActionsConfig Deserialize(const Json::Value& json, const ActionsConfig& default);
};

struct DateInputConfig
{
    SeparationConfig separation;

    static DateInputConfig Deserialize(const Json::Value& json, const DateInputConfig& default);
};

struct TimeInputConfig
{
    SeparationConfig separation;

    static TimeInputConfig Deserialize(const Json::Value& json, const TimeInputConfig& default);
};

struct NumberInputConfig
{
    SeparationConfig separation;

    static NumberInputConfig Deserialize(const Json::Value& json, const NumberInputConfig& default);
};

struct ToggleInputConfig
{
    SeparationConfig separation;

    static ToggleInputConfig Deserialize(const Json::Value& json, const ToggleInputConfig& default);
};

struct TextInputConfig
{
    SeparationConfig separation;

    static TextInputConfig Deserialize(const Json::Value& json, const TextInputConfig& default);
};

struct ChoiceSetConfig
{
    SeparationConfig separation;

    static ChoiceSetConfig Deserialize(const Json::Value& json, const ChoiceSetConfig& default);
};

struct HostConfig
{
    std::string fontFamily = "Calibri";
    FontSizesConfig fontSizes;
    bool supportsInteractivity = true;
    ColorsConfig colors;
    ImageSizesConfig imageSizes;
    unsigned int maxActions = 5;
    SeparationConfig strongSeparation = { 20, 1, "#FF707070" };
    AdaptiveCardConfig adaptiveCard;
    ImageSetConfig imageSet;
    ImageConfig image;
    FactSetConfig factSet;
    ColumnConfig column;
    ContainerConfig container;
    ColumnSetConfig columnSet;
    TextBlockConfig textBlock;
    DateInputConfig dateInput;
    TimeInputConfig timeInput;
    NumberInputConfig numberInput;
    ToggleInputConfig toggleInput;
    TextInputConfig textInput;
    ChoiceSetConfig choiceSet;
    ActionsConfig actions;

    static HostConfig Deserialize(const Json::Value& json);
    static HostConfig DeserializeFromString(const std::string jsonString);
};
}