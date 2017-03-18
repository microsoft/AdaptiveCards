#pragma once

#include<string>
#include <memory>
#include "Enums.h"
#include "ICardElement.h"

namespace AdaptiveCards
{
    class TextBlock : public ICardElement
    {
    public:
        TextBlock(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, Size size, std::wstring speak, std::wstring text, TextSize textSize, TextWeight textWeight, bool isSubtle, bool wrap);
        ~TextBlock();

        std::wstring GetText() const;
        void SetText(const std::wstring value);

        TextSize GetTextSize() const;
        void SetTextSize(const TextSize value);

        TextWeight GetTextWeight() const;
        void SetTextWeight(const TextWeight value);

        bool GetWrap() const;
        void SetWrap(const bool value);

        bool GetIsSubtle() const;
        void SetIsSubtle(const bool value);

    private:
        std::wstring m_text;
        TextSize m_textSize;
        TextWeight m_textWeight;
        bool m_isSubtle;
        bool m_wrap;
    };
}