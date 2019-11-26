// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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
    m_textSize(TextSize::Default), m_textWeight(TextWeight::Default), m_fontType(FontType::Default),
    m_textColor(ForegroundColor::Default), m_isSubtle(false), m_language()
{
}

TextElementProperties::TextElementProperties(const TextConfig& config, const std::string& text, const std::string& language) :
    m_text(text), m_textSize(config.size), m_textWeight(config.weight), m_fontType(config.fontType),
    m_textColor(config.color), m_isSubtle(config.isSubtle), m_language(language)
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

    if (m_fontType != FontType::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FontType)] = FontTypeToString(m_fontType);
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

FontType TextElementProperties::GetFontType() const
{
    return m_fontType;
}

void TextElementProperties::SetFontType(const FontType value)
{
    m_fontType = value;
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

void TextElementProperties::Deserialize(const ParseContext& context, const Json::Value& json)
{
    SetText(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Text, true));
    SetTextSize(ParseUtil::GetEnumValue<TextSize>(json, AdaptiveCardSchemaKey::Size, TextSize::Default, TextSizeFromString));
    SetTextColor(ParseUtil::GetEnumValue<ForegroundColor>(json, AdaptiveCardSchemaKey::Color, ForegroundColor::Default, ForegroundColorFromString));
    SetTextWeight(ParseUtil::GetEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::TextWeight, TextWeight::Default, TextWeightFromString));
    SetFontType(ParseUtil::GetEnumValue<FontType>(json, AdaptiveCardSchemaKey::FontType, FontType::Default, FontTypeFromString));
    SetIsSubtle(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsSubtle, false));
    SetLanguage(context.GetLanguage());
}

void TextElementProperties::PopulateKnownPropertiesSet(std::unordered_set<std::string>& knownProperties)
{
    knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Text),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Color),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::TextWeight),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FontType),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsSubtle)});
}
