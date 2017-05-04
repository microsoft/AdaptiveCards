#pragma once
#include "pch.h"

#ifdef _WIN32
#define strncasecmp _strnicmp
#endif // _WIN32

namespace AdaptiveCards
{

struct EnumHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

struct CaseInsensitiveEqualTo {
    bool operator() (const std::string& lhs, const std::string& rhs) const {
        return strncasecmp(lhs.c_str(), rhs.c_str(), CHAR_MAX) == 0;
    }
};

struct CaseInsensitiveHash {
    size_t operator() (const std::string& keyval) const {
        return std::accumulate(keyval.begin(), keyval.end(), 0, [](size_t acc, char c) { return acc + (size_t)std::tolower(c); });
    }
};

enum class AdaptiveCardSchemaKey
{
    Type = 0,
    Body,
    Version,
    MinVersion,
    FallbackText,
    BaseCardElement,
    Separation,
    Speak,
    Url,
    ImageStyle,
    ImageSize,
    AltText,
    HorizontalAlignment,
    Text,
    TextSize,
    TextWeight,
    TextColor,
    IsSubtle,
    Wrap,
    MaxLines,
    Items,
    Columns,
    Size,
    Facts,
    Title,
    Value,
    Images,
    Placeholder,
    IsMultiline,
    MaxLength,
    ValueOff,
    ValueOn,
    Max,
    Min,
    Choices,
    IsSelected,
    Style,
    IsMultiSelect,
    IsRequired,
};

enum class TextSize
{
    Small = 0,
    Normal,
    Medium,
    Large,
    ExtraLarge
};

enum class TextWeight {
    Lighter = 0,
    Normal,
    Bolder
};

enum class TextColor {
    Default = 0,
    Dark,
    Light,
    Accent,
    Good,
    Warning,
    Attention
};

enum class HorizontalAlignment {
    Left = 0,
    Center,
    Right
};

enum class ImageStyle {
    Normal = 0,
    Person
};

enum class ImageSize {
    Default = 0,
    Auto,
    Stretch,
    Small,
    Medium,
    Large
};

enum class CardElementType
{
    Unsupported = 0,
    AdaptiveCard,
    TextBlock,
    Image,
    Container,
    Column,
    ColumnSet,
    FactSet,
    Fact,
    ActionGroup,
    ImageSet,
    InputDate,
    InputText,
    InputTime,
    InputToggle,
    InputChoiceSet,
};

enum class ActionType
{
    ShowCard = 0,
    Submit,
    Http,
    OpenUrl
};

enum class ChoiceSetStyle
{
    Compact = 0,
    Expanded
};

enum class SeparationStyle {
    Default = 0,
    None,
    Strong,
};

enum class ActionsOrientation {
    Vertical = 0,
    Horizontal
};

enum class ActionMode {
    Inline = 0,
    Popup
};

const std::string AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey type);
AdaptiveCardSchemaKey AdaptiveCardSchemaKeyFromString(const std::string& type);

const std::string CardElementTypeToString(CardElementType elementType);
CardElementType CardElementTypeFromString(const std::string& elementType);

const std::string ActionTypeToString(ActionType elementType);
ActionType ActionTypeFromString(const std::string& elementType);

const std::string HorizontalAlignmentToString(HorizontalAlignment type);
HorizontalAlignment HorizontalAlignmentFromString(const std::string& type);

const std::string TextColorToString(TextColor type);
TextColor TextColorFromString(const std::string& type);

const std::string TextWeightToString(TextWeight type);
TextWeight TextWeightFromString(const std::string& type);

const std::string TextSizeToString(TextSize type);
TextSize TextSizeFromString(const std::string& type);

const std::string ImageSizeToString(ImageSize type);
ImageSize ImageSizeFromString(const std::string& type);

const std::string SeparationStyleToString(SeparationStyle type);
SeparationStyle SeparationStyleFromString(const std::string& type);

const std::string ImageStyleToString(ImageStyle style);
ImageStyle ImageStyleFromString(const std::string& style);

const std::string ActionsOrientationToString(ActionsOrientation style);
ActionsOrientation ActionsOrientationFromString(const std::string& style);

const std::string ActionModeToString(ActionMode style);
ActionMode ActionModeFromString(const std::string& style);

const std::string ChoiceSetStyleToString(ChoiceSetStyle type);
ChoiceSetStyle ChoiceSetStyleFromString(const std::string& type);

}
