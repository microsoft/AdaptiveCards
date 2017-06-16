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
};

struct FontSizesConfig
{
    unsigned int smallFontSize = 10;
    unsigned int normalFontSize = 12;
    unsigned int mediumFontSize = 14;
    unsigned int largeFontSize = 17;
    unsigned int extraLargeFontSize = 20;
};

struct ColorConfig
{
    std::string normal;
    std::string subtle;
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
};

struct TextConfig
{
    TextWeight weight = TextWeight::Normal;
    TextSize size = TextSize::Normal;
    TextColor color = TextColor::Default;
    bool isSubtle = false;
};

struct SeparationConfig
{
    unsigned int spacing = 10;
    unsigned int lineThickness = 0;
    std::string lineColor = "#FF101010";
};
struct ImageSizesConfig
{
    unsigned int smallSize = 80;
    unsigned int mediumSize = 120;
    unsigned int largeSize = 180;
};

struct TextBlockConfig
{
    SeparationConfig smallSeparation;
    SeparationConfig normalSeparation;
    SeparationConfig mediumSeparation;
    SeparationConfig largeSeparation;
    SeparationConfig extraLargeSeparation;
};

struct ImageSetConfig
{
    ImageSize imageSize = ImageSize::Medium;
    SeparationConfig separation;
};

struct ColumnConfig
{
    SeparationConfig separation;
};

struct ContainerStyleConfig
{
    std::string backgroundColor = "#00FFFFFF";
    std::string borderColor = "#00FFFFFF";
    SpacingDefinition borderThickness;
    SpacingDefinition padding;
};

struct ContainerConfig
{
    SeparationConfig separation;
    ContainerStyleConfig normal;
    ContainerStyleConfig emphasis = { "#FFEEEEEE", "#FFAAAAAA", SpacingDefinition{ 1, 1, 1, 1 }, SpacingDefinition{10, 10, 10, 10 } };
};

struct ColumnSetConfig
{
    SeparationConfig separation;
};

struct ImageConfig
{
    SeparationConfig separation;
};

struct AdaptiveCardConfig
{
    SpacingDefinition padding = { 8, 8, 8, 8 };
    std::string backgroundColor = "#FFFFFFFF";
};

struct FactSetConfig
{
    TextConfig title = { TextWeight::Bolder };
    TextConfig value;
    unsigned int spacing = 20;
    SeparationConfig separation;
};

struct ShowCardActionConfig
{
    ActionMode actionMode = ActionMode::InlineEdgeToEdge;
    std::string backgroundColor = "#FFF8F8F8";
    unsigned int inlineTopMargin = 16;
    SpacingDefinition padding = { 16, 16, 16, 16 };
};

struct ActionsConfig
{
    ShowCardActionConfig showCard;
    ActionsOrientation actionsOrientation = ActionsOrientation::Horizontal;
    ActionAlignment actionAlignment = ActionAlignment::Center;
    unsigned int buttonSpacing = 8;
    unsigned int maxActions = 5;
    SeparationConfig separation;
};

struct DateInputConfig
{
    SeparationConfig separation;
};

struct TimeInputConfig
{
    SeparationConfig separation;
};

struct NumberInputConfig
{
    SeparationConfig separation;
};

struct ToggleInputConfig
{
    SeparationConfig separation;
};

struct TextInputConfig
{
    SeparationConfig separation;
};

struct ChoiceSetConfig
{
    SeparationConfig separation;
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
};
}