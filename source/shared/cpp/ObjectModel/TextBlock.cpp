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

using namespace AdaptiveSharedNamespace;

TextBlock::TextBlock() :
    BaseCardElement(CardElementType::TextBlock), m_wrap(false), m_maxLines(0), m_hAlignment(HorizontalAlignment::Left),
    m_textElementProperties(std::make_shared<TextElementProperties>())
{
    PopulateKnownPropertiesSet();
}

Json::Value TextBlock::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    // ignore return -- properties are added directly to root
    (void)m_textElementProperties->SerializeToJsonValue(root);

    if (m_hAlignment != HorizontalAlignment::Left)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment)] = HorizontalAlignmentToString(m_hAlignment);
    }

    if (m_maxLines != 0)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MaxLines)] = m_maxLines;
    }

    if (m_wrap)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Wrap)] = true;
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

TextSize TextBlock::GetTextSize() const
{
    return m_textElementProperties->GetTextSize();
}

void TextBlock::SetTextSize(const TextSize value)
{
    m_textElementProperties->SetTextSize(value);
}

TextWeight TextBlock::GetTextWeight() const
{
    return m_textElementProperties->GetTextWeight();
}

void TextBlock::SetTextWeight(const TextWeight value)
{
    m_textElementProperties->SetTextWeight(value);
}

FontType TextBlock::GetFontType() const
{
    return m_textElementProperties->GetFontType();
}

void TextBlock::SetFontType(const FontType value)
{
    m_textElementProperties->SetFontType(value);
}

ForegroundColor TextBlock::GetTextColor() const
{
    return m_textElementProperties->GetTextColor();
}

void TextBlock::SetTextColor(const ForegroundColor value)
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

bool TextBlock::GetIsSubtle() const
{
    return m_textElementProperties->GetIsSubtle();
}

void TextBlock::SetIsSubtle(const bool value)
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

HorizontalAlignment TextBlock::GetHorizontalAlignment() const
{
    return m_hAlignment;
}

void TextBlock::SetHorizontalAlignment(const HorizontalAlignment value)
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
    textBlock->SetMaxLines(ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxLines, 0));
    textBlock->SetHorizontalAlignment(ParseUtil::GetEnumValue<HorizontalAlignment>(
        json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString));

    return textBlock;
}

std::shared_ptr<BaseCardElement> TextBlockParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return TextBlockParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void TextBlock::PopulateKnownPropertiesSet()
{
    m_textElementProperties->PopulateKnownPropertiesSet(m_knownProperties);

    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Wrap),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MaxLines),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment)});
}
