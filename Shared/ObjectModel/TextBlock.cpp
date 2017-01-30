#include "TextBlock.h"

namespace AdaptiveCards
{
    AdaptiveCards::TextBlock::TextBlock(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, Size size, std::wstring speak, std::wstring text, TextSize textSize, TextWeight textWeight, bool isSubtle, bool wrap) : ICardElement(container, horizontalAlignment, size, speak), m_text(text), m_textSize(textSize), m_textWeight(textWeight), m_isSubtle(isSubtle), m_wrap(wrap) {}

    TextBlock::~TextBlock() {}

    std::wstring TextBlock::GetText() const
    {
        return m_text;
    }

    void TextBlock::SetText(const std::wstring value)
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
