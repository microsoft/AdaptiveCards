#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"

namespace AdaptiveCards
{
struct BoundaryOptions
{
    unsigned int left = 0;
    unsigned int right = 0;
    unsigned int top = 0;
    unsigned int bottom = 0;
};

struct FontSizeOptions
{
    unsigned int smallFontSize = 10;
    unsigned int normalFontSize = 12;
    unsigned int mediumFontSize = 14;
    unsigned int largeFontSize = 17;
    unsigned int extraLargeFontSize = 20;
};

struct ColorOption
{
    std::string normal;
    std::string subtle;
};

struct ColorOptions
{
    ColorOption defaultColor = { "#FF000000", "#B2000000" };
    ColorOption accent = { "#FF0000FF", "#B20000FF" };
    ColorOption dark = { "#FF101010", "#B2101010" };
    ColorOption light = { "#FFFFFFFF", "#B2FFFFFF" };
    ColorOption good = { "#FF008000", "#B2008000" };
    ColorOption warning = { "#FFFFD700", "#B2FFD700" };
    ColorOption attention = { "#FF8B0000", "#B28B0000" };
};

struct TextOptions
{
    TextWeight weight = TextWeight::Normal;
    TextSize size = TextSize::Normal;
    TextColor color = TextColor::Default;
    bool isSubtle = false;
};

struct SeparationOptions
{
    unsigned int spacing = 10;
    unsigned int lineThickness = 0;
    std::string lineColor;
};
struct ImageSizeOptions
{
    unsigned int smallSize = 60;
    unsigned int mediumSize = 120;
    unsigned int largeSize = 180;
};

struct TextBlockOptions
{
    SeparationOptions smallSeparation;
    SeparationOptions normalSeparation;
    SeparationOptions mediumSeparation;
    SeparationOptions largeSeparation;
    SeparationOptions extraLargeSeparation;
};

struct ImageSetOptions
{
    ImageSize imageSize = ImageSize::Medium;
    SeparationOptions separation;
};

struct ColumnOptions
{
    SeparationOptions separation;
};

struct ContainerStyleConfig
{
    std::string backgroundColor;
    std::string borderColor;
    BoundaryOptions borderThickness;
    BoundaryOptions padding;
};

struct ContainerOptions
{
    SeparationOptions separation;
    ContainerStyleConfig normal;
    ContainerStyleConfig emphasis;
};

struct ColumnSetOptions
{
    SeparationOptions separation;
};

struct ImageOptions
{
    SeparationOptions separation;
};

struct AdaptiveCardOptions
{
    BoundaryOptions padding = { 8, 8, 8, 8 };
    std::string backgroundColor = "#FFFFFFFF";
};

struct FactSetOptions
{
    TextOptions title = { TextWeight::Bolder };
    TextOptions value;
    unsigned int spacing = 20;
    SeparationOptions separation;
};

struct ShowCardOptions
{
    ActionMode actionMode = ActionMode::Inline;
    std::string backgroundColor = "#FFF8F8F8";
    bool autoPadding = true;
};

struct ActionOptions
{
    ShowCardOptions showCard;
    ActionsOrientation actionsOrientation = ActionsOrientation::Horizontal;
    ActionAlignment actionAlignment = ActionAlignment::Center;
    unsigned int buttonSpacing = 8;
    unsigned int maxActions = 5;
    SeparationOptions separation;
};

struct DateInputOptions
{
    SeparationOptions separation;
};

struct TimeInputOptions
{
    SeparationOptions separation;
};

struct NumberInputOptions
{
    SeparationOptions separation;
};

struct ToggleInputOptions
{
    SeparationOptions separation;
};

struct TextInputOptions
{
    SeparationOptions separation;
};

struct ChoiceSetOptions
{
    SeparationOptions separation;
};

struct HostOptions
{
    std::string fontFamily = "Calibri";
    FontSizeOptions fontSizes;
    bool supportsInteractivity = true;
    ColorOptions colors;
    ImageSizeOptions imageSizes;
    unsigned int maxActions = 5;
    SeparationOptions strongSeparation = { 20, 1, "#FF707070" };
    AdaptiveCardOptions adaptiveCard;
    ImageSetOptions imageSet;
    ImageOptions image;
    FactSetOptions factSet;
    ColumnOptions column;
    ContainerOptions container;
    ColumnSetOptions columnSet;
    TextBlockOptions textBlock;
    DateInputOptions dateInput;
    TimeInputOptions timeInput;
    NumberInputOptions numberInput;
    ToggleInputOptions toggleInput;
    TextInputOptions textInput;
    ChoiceSetOptions choiceSet;
    ActionOptions actions;
};
}