#pragma once
#include "pch.h"

#define _strnicmp strncasecmp

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
        return _strnicmp(lhs.c_str(), rhs.c_str(), CHAR_MAX) == 0;
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
    Size
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
    Auto = 0,
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
    FactGroup,
    ImageGallery,
    ActionGroup
};

enum class SeparationStyle {
    Default = 0,
    None,
    Strong,
};

const std::string AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey type);
AdaptiveCardSchemaKey AdaptiveCardSchemaKeyFromString(const std::string& type);

const std::string CardElementTypeToString(CardElementType elementType);
CardElementType CardElementTypeFromString(const std::string& elementType);

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

}
