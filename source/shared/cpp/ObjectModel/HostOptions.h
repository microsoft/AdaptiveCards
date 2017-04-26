#pragma once

#include "pch.h"
#include "Enums.h"
#include "json\json.h"

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
    int small = 10;
    int normal = 12;
    int medium = 14;
    int large = 17;
    int extraLarge = 20;
};

struct ColorOption
{
    std::string normal;
    std::string subtle;
};

struct ColorOptions
{
    ColorOption defaultColor = { "#FF000000" };
    ColorOption accent = { "#FF0000FF" };
    ColorOption dark = { "#FF101010" };
    ColorOption light = { "#FFFFFFFF" };
    ColorOption good = { "#FF008000" };
    ColorOption warning = { "#FFFFD700" };
    ColorOption attention = { "#FF8B0000" };
};

struct TextOptions
{
    TextWeight weight = TextWeight::Normal;
    TextSize size = TextSize::Normal;
    TextColor color = TextColor::Default;
    bool isSubtle = false;
};

struct SeparationOption
{
    int spacing = 10;
    int lineThickness = 0;
    std::string lineColor;
};
struct ImageSizeOptions
{
    int small = 60;
    int medium = 120;
    int large = 180;
};

struct TextBlockOptions
{
    SeparationOption small;
    SeparationOption normal;
    SeparationOption medium;
    SeparationOption large;
    SeparationOption extraLarge;
};

struct ImageSetOptions
{
    ImageSize imageSize = ImageSize::Medium;
    SeparationOption separation;
};

struct ColumnOptions
{
    SeparationOption defaultSeparation;
    SeparationOption strong = { 20, 1, "#FF707070" };
};

struct ContainerOptions
{
    SeparationOption separation;
};

struct ColumnSetOptions
{
    SeparationOption separation;
};

struct ImageOptions
{
    SeparationOption separation;
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
    SeparationOption separation;
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
    SeparationOption separation;
};

struct TimeInputOptions
{
    SeparationOption separation;
};

struct NumberInputOptions
{
    SeparationOption separation;
};

struct ToggleInputOptions
{
    SeparationOption separation;
};

struct TextInputOptions
{
    SeparationOption separation;
};

struct ChoiceSetOptions
{
    SeparationOption separation;
};

struct HostOptions
{
    std::string fontFamily = "Calibri";
    FontSizeOptions fontSizes;
    bool supportsInteractivity = true;
    ColorOptions colors;
    ImageSizeOptions imageSizes;
    int maxActions = 5;
    SeparationOption strongSeparation = { 20, 1, "#FF707070" };
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