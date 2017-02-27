#include "TextBlock.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

TextBlock::TextBlock() : 
    BaseCardElement(CardElementType::TextBlock),
    m_textSize(TextSize::Normal),
    m_textWeight(TextWeight::Normal),
    m_textColor(TextColor::Default),
    m_isSubtle(false),
    m_wrap(false)
{
}

TextBlock::TextBlock(std::shared_ptr<Container> container,
    HorizontalAlignment horizontalAlignment,
    CardElementSize size,
    std::string speak,
    std::string text,
    TextSize textSize,
    TextWeight textWeight,
    TextColor textColor,
    bool isSubtle,
    bool wrap) :
    BaseCardElement(CardElementType::TextBlock, container, horizontalAlignment, size, speak),
    m_text(text),
    m_textSize(textSize),
    m_textWeight(textWeight),
    m_textColor(textColor),
    m_isSubtle(isSubtle),
    m_wrap(wrap)
{
}

std::shared_ptr<TextBlock> TextBlock::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::TextBlock);

    std::shared_ptr<TextBlock> textBlock = BaseCardElement::Deserialize<TextBlock>(json);

    std::string text = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Text);
    textBlock->SetText(text);
    TextSize textSize = ParseUtil::GetEnumValue<TextSize>(json, AdaptiveCardSchemaKey::TextSize, TextSize::Normal, TextSizeFromString);
    textBlock->SetTextSize(textSize);
    TextColor textColor = ParseUtil::GetEnumValue<TextColor>(json, AdaptiveCardSchemaKey::TextColor, TextColor::Default, TextColorFromString);
    textBlock->SetTextColor(textColor);
    TextWeight textWeight = ParseUtil::GetEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::TextWeight, TextWeight::Normal, TextWeightFromString);
    textBlock->SetTextWeight(textWeight);
    TextWrap textWrap = ParseUtil::GetEnumValue<TextWrap>(json, AdaptiveCardSchemaKey::TextWrap, TextWrap::NoWrap, TextWrapFromString);
    textBlock->SetWrap(textWrap == TextWrap::Wrap);
    textBlock->SetIsSubtle(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::isSubtle, false));
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

TextColor TextBlock::GetTextColor() const
{
    return m_textColor;
}

void TextBlock::SetTextColor(const TextColor value)
{
    m_textColor = value;
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
