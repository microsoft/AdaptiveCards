#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"

namespace AdaptiveCards
{
struct BoundaryOptions
{
    int left = 0;
    int right = 0;
    int bottom = 0;
    int top = 0;
};

struct FontSizeOptions
{
    int smallFontSize = 10;
    int normalFontSize = 12;
    int mediumFontSize = 14;
    int largeFontSize = 17;
    int extraLargeFontSize = 20;
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
    int spacing = 10;
    int lineThickness = 0;
    std::string lineColor;
};
struct ImageSizeOptions
{
    int smallSize = 60;
    int mediumSize = 120;
    int largeSize = 180;
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

struct ContainerOptions
{
    SeparationOptions separation;
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
    std::string borderColor = "#FFFFFFFF";
    int maxActions = 5;
    ActionsOrientation actionsOrientation = ActionsOrientation::Horizontal;
    HorizontalAlignment actionAlignment = HorizontalAlignment::Center;
    std::string textColor = "#FF000000";
    std::string backgroundColor = "#FF5098FF";
};

struct FactSetOptions
{
    TextOptions title = { TextWeight::Bolder };
    TextOptions value;
    int spacing = 20;
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
    ActionsOrientation actionsOrientation;
    HorizontalAlignment actionAlignment;
    std::string backgroundColor = "#FF5098FF";
    std::string borderColor = "#FF000000";
    std::string textColor = "FFFFFFFF";
    int borderThickness = 1;
    int fontWeight = 400;
    int fontSize = 12;
    int spacing = 8;
    BoundaryOptions padding = { 4, 4, 4, 4 };
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
    int maxActions = 5;
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