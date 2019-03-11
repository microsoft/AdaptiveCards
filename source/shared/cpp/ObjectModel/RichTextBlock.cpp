#include "pch.h"
#include <iomanip>
#include <regex>
#include <iostream>
#include <codecvt>
#include "ParseContext.h"
#include "RichTextBlock.h"
#include "DateTimePreparser.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

RichTextBlock::RichTextBlock() :
    BaseCardElement(CardElementType::RichTextBlock), m_wrap(false), m_maxLines(0),
    m_hAlignment(HorizontalAlignment::Left)
{
    PopulateKnownPropertiesSet();
}

Json::Value RichTextBlock::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

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

    std::string paragraphsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Paragraphs);
    root[paragraphsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& paragraph : GetParagraphs())
    {
        root[paragraphsPropertyName].append(paragraph->SerializeToJsonValue());
    }

    return root;
}

bool RichTextBlock::GetWrap() const
{
    return m_wrap;
}

void RichTextBlock::SetWrap(const bool value)
{
    m_wrap = value;
}

unsigned int RichTextBlock::GetMaxLines() const
{
    return m_maxLines;
}

void RichTextBlock::SetMaxLines(const unsigned int value)
{
    m_maxLines = value;
}

HorizontalAlignment RichTextBlock::GetHorizontalAlignment() const
{
    return m_hAlignment;
}

void RichTextBlock::SetHorizontalAlignment(const HorizontalAlignment value)
{
    m_hAlignment = value;
}

std::vector<std::shared_ptr<Paragraph>>& RichTextBlock::GetParagraphs()
{
    return m_paragraphs;
}

const std::vector<std::shared_ptr<Paragraph>>& RichTextBlock::GetParagraphs() const
{
    return m_paragraphs;
}

std::shared_ptr<BaseCardElement> RichTextBlockParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::RichTextBlock);

    std::shared_ptr<RichTextBlock> richTextBlock = BaseCardElement::Deserialize<RichTextBlock>(context, json);
    richTextBlock->SetWrap(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Wrap, false));
    richTextBlock->SetMaxLines(ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxLines, 0));
    richTextBlock->SetHorizontalAlignment(ParseUtil::GetEnumValue<HorizontalAlignment>(
        json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString));

    auto paragraphs =
        ParseUtil::GetElementCollectionOfSingleType<Paragraph>(context, json, AdaptiveCardSchemaKey::Paragraphs, Paragraph::Deserialize, true);
    richTextBlock->m_paragraphs = std::move(paragraphs);
    
    return richTextBlock;
}

std::shared_ptr<BaseCardElement> RichTextBlockParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return RichTextBlockParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void RichTextBlock::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Paragraphs),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MaxLines),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Wrap)});
}
