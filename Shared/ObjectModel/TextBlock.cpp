#include "TextBlock.h"
#include "ACParser.h"

namespace AdaptiveCards
{

TextBlock::TextBlock() : ICardElement(nullptr, HorizontalAlignment::Left, Size::Auto, "")
{
}

TextBlock::TextBlock(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, Size size, std::string speak, std::string text, TextSize textSize, TextWeight textWeight, bool isSubtle, bool wrap) : ICardElement(container, horizontalAlignment, size, speak), m_text(text), m_textSize(textSize), m_textWeight(textWeight), m_isSubtle(isSubtle), m_wrap(wrap) {}

TextBlock::~TextBlock() {}

std::shared_ptr<TextBlock> TextBlock::Deserialize(const Json::Value& json)
{
    ACParser::ThrowIfNotJsonObject(json);
    ACParser::ExpectTypeString(json, CardElementType::TextBlockType);

    // Parse text field
    std::string speak = ACParser::GetString(json, AdaptiveCardSchemaKey::Speak);
    std::string text = ACParser::GetString(json, AdaptiveCardSchemaKey::Text);
    Size size = ACParser::GetEnumValue<Size>(json, AdaptiveCardSchemaKey::Size, Size::Auto, SizeFromString);

    TextSize textSize = ACParser::GetEnumValue<TextSize>(json, AdaptiveCardSchemaKey::TextSize, TextSize::Normal, TextSizeFromString);
    TextColor textColor = ACParser::GetEnumValue<TextColor>(json, AdaptiveCardSchemaKey::TextColor, TextColor::Default, TextColorFromString);
    TextWeight textWeight = ACParser::GetEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::TextWeight, TextWeight::Normal, TextWeightFromString);
    TextWrap textWrap = ACParser::GetEnumValue<TextWrap>(json, AdaptiveCardSchemaKey::TextWrap, TextWrap::NoWrap, TextWrapFromString);
    HorizontalAlignment horAlignment = ACParser::GetEnumValue<HorizontalAlignment>(json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString);

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
}
