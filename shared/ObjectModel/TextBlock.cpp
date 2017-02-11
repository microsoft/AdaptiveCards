#include "TextBlock.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

TextBlock::TextBlock() : BaseCardElement(CardElementType::TextBlock, nullptr, HorizontalAlignment::Left, CardElementSize::Auto, "")
{
}

TextBlock::TextBlock(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, CardElementSize size, std::string speak,
    std::string text, TextSize textSize, TextWeight textWeight, bool isSubtle, bool wrap) : 
    BaseCardElement(CardElementType::TextBlock, container, horizontalAlignment, size, speak),
    m_text(text),
    m_textSize(textSize),
    m_textWeight(textWeight),
    m_isSubtle(isSubtle),
    m_wrap(wrap) 
{
}

std::shared_ptr<TextBlock> TextBlock::Deserialize(const Json::Value& json)
{
    ParseUtil::ThrowIfNotJsonObject(json);
    ParseUtil::ExpectTypeString(json, CardElementType::TextBlock);

    // Parse text field
    std::string speak = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Speak);
    std::string text = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Text);
    CardElementSize size = ParseUtil::GetEnumValue<CardElementSize>(json, AdaptiveCardSchemaKey::CardElementSize, CardElementSize::Auto, SizeFromString);

    TextSize textSize = ParseUtil::GetEnumValue<TextSize>(json, AdaptiveCardSchemaKey::TextSize, TextSize::Normal, TextSizeFromString);
    TextColor textColor = ParseUtil::GetEnumValue<TextColor>(json, AdaptiveCardSchemaKey::TextColor, TextColor::Default, TextColorFromString);
    TextWeight textWeight = ParseUtil::GetEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::TextWeight, TextWeight::Normal, TextWeightFromString);
    TextWrap textWrap = ParseUtil::GetEnumValue<TextWrap>(json, AdaptiveCardSchemaKey::TextWrap, TextWrap::NoWrap, TextWrapFromString);
    HorizontalAlignment horAlignment = ParseUtil::GetEnumValue<HorizontalAlignment>(json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString);

    auto textBlock = std::make_shared<TextBlock>(nullptr, horAlignment, size, speak, text, textSize, textWeight, false, textWrap == TextWrap::Wrap);
    return textBlock;
}

std::string TextBlock::Serialize()
{
    return "";
}

std::string TextBlock::GetText() const
{
    return m_text;
}

void TextBlock::SetText(const std::string value)
{
    m_text = value;
}

TextSize TextBlock::GetTextSize() const
{
    return m_textSize;
}

void TextBlock::SetTextSize(const TextSize value)
{
    m_textSize = value;
}

TextWeight TextBlock::GetTextWeight() const
{
    return m_textWeight;
}

void TextBlock::SetTextWeight(const TextWeight value)
{
    m_textWeight = value;
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
    return m_isSubtle;
}

void TextBlock::SetIsSubtle(const bool value)
{
    m_isSubtle = value;
}
