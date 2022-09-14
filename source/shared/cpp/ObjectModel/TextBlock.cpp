// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include <iomanip>
#include <regex>
#include <iostream>
#include <codecvt>
#include "ParseContext.h"
#include "TextBlock.h"
#include "DateTimePreparser.h"
#include "ParseUtil.h"
#include "Util.h"

using namespace AdaptiveCards;

TextBlock::TextBlock() :
    BaseCardElement(CardElementType::TextBlock), m_wrap(false), m_maxLines(0), m_hAlignment(std::nullopt),
    m_textElementProperties(std::make_shared<TextElementProperties>())
{
    PopulateKnownPropertiesSet();
}

Json::Value TextBlock::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    // ignore return -- properties are added directly to root
    (void)m_textElementProperties->SerializeToJsonValue(root);

    if (m_hAlignment.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment)] =
            HorizontalAlignmentToString(m_hAlignment.value_or(HorizontalAlignment::Left));
    }

    if (m_maxLines != 0)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MaxLines)] = m_maxLines;
    }

    if (m_wrap)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Wrap)] = m_wrap;
    }

    if (m_textStyle.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] =
            TextStyleToString(m_textStyle.value_or(TextStyle::Default));
    }

    return root;
}

std::string TextBlock::GetText() const
{
    return m_textElementProperties->GetText();
}

void TextBlock::SetText(const std::string& value)
{
    m_textElementProperties->SetText(value);
}

DateTimePreparser TextBlock::GetTextForDateParsing() const
{
    return m_textElementProperties->GetTextForDateParsing();
}

std::optional<TextStyle> TextBlock::GetStyle() const
{
    return m_textStyle;
}

void TextBlock::SetStyle(const std::optional<TextStyle> value)
{
    m_textStyle = value;
}

std::optional<TextSize> TextBlock::GetTextSize() const
{
    return m_textElementProperties->GetTextSize();
}

void TextBlock::SetTextSize(const std::optional<TextSize> value)
{
    m_textElementProperties->SetTextSize(value);
}

std::optional<TextWeight> TextBlock::GetTextWeight() const
{
    return m_textElementProperties->GetTextWeight();
}

void TextBlock::SetTextWeight(const std::optional<TextWeight> value)
{
    m_textElementProperties->SetTextWeight(value);
}

std::optional<FontType> TextBlock::GetFontType() const
{
    return m_textElementProperties->GetFontType();
}

void TextBlock::SetFontType(const std::optional<FontType> value)
{
    m_textElementProperties->SetFontType(value);
}

std::optional<ForegroundColor> TextBlock::GetTextColor() const
{
    return m_textElementProperties->GetTextColor();
}

void TextBlock::SetTextColor(const std::optional<ForegroundColor> value)
{
    m_textElementProperties->SetTextColor(value);
}

bool TextBlock::GetWrap() const
{
    return m_wrap;
}

void TextBlock::SetWrap(const bool value)
{
    m_wrap = value;
}

std::optional<bool> TextBlock::GetIsSubtle() const
{
    return m_textElementProperties->GetIsSubtle();
}

void TextBlock::SetIsSubtle(const std::optional<bool> value)
{
    m_textElementProperties->SetIsSubtle(value);
}

unsigned int TextBlock::GetMaxLines() const
{
    return m_maxLines;
}

void TextBlock::SetMaxLines(const unsigned int value)
{
    m_maxLines = value;
}

std::optional<HorizontalAlignment> TextBlock::GetHorizontalAlignment() const
{
    return m_hAlignment;
}

void TextBlock::SetHorizontalAlignment(const std::optional<HorizontalAlignment> value)
{
    m_hAlignment = value;
}

const std::string& TextBlock::GetLanguage() const
{
    return m_textElementProperties->GetLanguage();
}

void TextBlock::SetLanguage(const std::string& value)
{
    m_textElementProperties->SetLanguage(value);
}

std::shared_ptr<BaseCardElement> TextBlockParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::TextBlock);

    std::shared_ptr<TextBlock> textBlock = BaseCardElement::Deserialize<TextBlock>(context, json);
    textBlock->m_textElementProperties->Deserialize(context, json);

    textBlock->SetWrap(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Wrap, false));
    textBlock->SetStyle(ParseUtil::GetOptionalEnumValue<TextStyle>(json, AdaptiveCardSchemaKey::Style, TextStyleFromString));
    textBlock->SetMaxLines(ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxLines, 0));
    textBlock->SetHorizontalAlignment(ParseUtil::GetOptionalEnumValue<HorizontalAlignment>(
        json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignmentFromString));

    return textBlock;
}

std::shared_ptr<BaseCardElement> TextBlockParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return TextBlockParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void TextBlock::PopulateKnownPropertiesSet()
{
    m_textElementProperties->PopulateKnownPropertiesSet(m_knownProperties);

    m_knownProperties.insert(
        {AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Wrap),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MaxLines),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment)});
}
