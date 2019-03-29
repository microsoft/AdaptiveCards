#include "pch.h"
#include <iomanip>
#include <regex>
#include <iostream>
#include <codecvt>
#include "ParseContext.h"
#include "TextElementProperties.h"
#include "DateTimePreparser.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

TextElementProperties::TextElementProperties() :
    m_textSize(TextSize::Default), m_textWeight(TextWeight::Default), m_fontStyle(FontStyle::Default),
    m_textColor(ForegroundColor::Default), m_isSubtle(false), m_language()
{
}

Json::Value TextElementProperties::SerializeToJsonValue(Json::Value& root) const
{
    if (m_textSize != TextSize::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size)] = TextSizeToString(m_textSize);
    }

    if (m_textColor != ForegroundColor::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Color)] = ForegroundColorToString(m_textColor);
    }

    if (m_textWeight != TextWeight::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Weight)] = TextWeightToString(m_textWeight);
    }

    if (m_fontStyle != FontStyle::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FontStyle)] = FontStyleToString(m_fontStyle);
    }

    if (m_isSubtle)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsSubtle)] = true;
    }

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Text)] = GetText();

    return root;
}

std::string TextElementProperties::GetText() const
{
    return m_text;
}

void TextElementProperties::SetText(const std::string& value)
{
    m_text = value;
}

DateTimePreparser TextElementProperties::GetTextForDateParsing() const
{
    return DateTimePreparser(m_text);
}

TextSize TextElementProperties::GetTextSize() const
{
    return m_textSize;
}

void TextElementProperties::SetTextSize(const TextSize value)
{
    m_textSize = value;
}

TextWeight TextElementProperties::GetTextWeight() const
{
    return m_textWeight;
}

void TextElementProperties::SetTextWeight(const TextWeight value)
{
    m_textWeight = value;
}

FontStyle TextElementProperties::GetFontStyle() const
{
    return m_fontStyle;
}

void TextElementProperties::SetFontStyle(const FontStyle value)
{
    m_fontStyle = value;
}

ForegroundColor TextElementProperties::GetTextColor() const
{
    return m_textColor;
}

void TextElementProperties::SetTextColor(const ForegroundColor value)
{
    m_textColor = value;
}

bool TextElementProperties::GetIsSubtle() const
{
    return m_isSubtle;
}

void TextElementProperties::SetIsSubtle(const bool value)
{
    m_isSubtle = value;
}

std::string TextElementProperties::GetLanguage() const
{
    return m_language;
}

void TextElementProperties::SetLanguage(const std::string& value)
{
    m_language = value;
}

void TextElementProperties::Deserialize(ParseContext& context, const Json::Value& json)
{
    SetText(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Text, true));
    SetTextSize(ParseUtil::GetEnumValue<TextSize>(json, AdaptiveCardSchemaKey::Size, TextSize::Default, TextSizeFromString));
    SetTextColor(ParseUtil::GetEnumValue<ForegroundColor>(json, AdaptiveCardSchemaKey::Color, ForegroundColor::Default, ForegroundColorFromString));
    SetTextWeight(ParseUtil::GetEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::TextWeight, TextWeight::Default, TextWeightFromString));
    SetFontStyle(ParseUtil::GetEnumValue<FontStyle>(json, AdaptiveCardSchemaKey::FontStyle, FontStyle::Default, FontStyleFromString));
    SetIsSubtle(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsSubtle, false));
    SetLanguage(context.GetLanguage());
}

void TextElementProperties::PopulateKnownPropertiesSet(std::unordered_set<std::string>& knownProperties)
{
    knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Text),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Color),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::TextWeight),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FontStyle),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsSubtle)});
}
