#pragma once

#include <memory>
#include <string>
#include "enums.h"

namespace AdaptiveCards
{
    class ICardElement
    {
    public:
        ICardElement(HorizontalAlignment horizontalAlignment, Size size, std::wstring speak);
        ICardElement();
        virtual ~ICardElement() = 0 {};

        HorizontalAlignment GetHorizontalAlignment() const;
        void SetHorizontalAlignment(const HorizontalAlignment value);

        Size GetSize() const;
        void SetSize(const Size value);

        std::wstring GetSpeak() const;
        void SetSpeak(const std::wstring value);

    private:
        HorizontalAlignment m_horizontalAlignment;
        Size m_size;
        std::wstring m_speak;
    };
}

