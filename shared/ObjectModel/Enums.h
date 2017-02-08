#pragma once
#include "pch.h"

namespace AdaptiveCards
{

enum class AdaptiveCardSchemaKey
{
    Size = 0,
    TextSize,
    TextWeight,
    TextWrap,
    TextColor,
    HorizontalAlignment,
    ImageStyle,
    BaseCardElement,
    Text,
    Speak,
    Type,
};

enum class Size
{
    Auto = 0,
    Stretch,
    Small,
    Medium,
    Large
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

enum class TextWrap {
    NoWrap = 0,
    Wrap,
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

enum class CardElementType
{
    AdaptiveCardType = 0,
    TextBlockType,
    ImageType,
    FactGroupType,
    ColumnGroupType,
    ImageGalleryType,
    ActionGroupType,
    ContainerType,
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

const std::string SizeToString(Size type);
Size SizeFromString(const std::string& type);

const std::string TextWrapToString(TextWrap type);
TextWrap TextWrapFromString(const std::string& type);

}
