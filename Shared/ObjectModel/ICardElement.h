#pragma once

#include <memory>
#include "enums.h"
#include "container.h"

namespace AdaptiveCards
{
    class ICardElement
    {
    public:
        ICardElement(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, Size size, std::wstring speak);
        virtual ~ICardElement() = 0 {};

        std::shared_ptr<Container> GetContainer() const;

        HorizontalAlignment GetHorizontalAlignment() const;
        void SetHorizontalAlignment(const HorizontalAlignment value);

        Size GetSize() const;
        void SetSize(const Size value);

        std::wstring GetSpeak() const;
        void SetSpeak(const std::wstring value);

    private:
        std::weak_ptr<Container> m_container;
        HorizontalAlignment m_horizontalAlignment;
        Size m_size;
        std::wstring m_speak;
    };
}

