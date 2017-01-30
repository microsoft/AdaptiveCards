#include "ICardElement.h"

namespace AdaptiveCards
{
    ICardElement::ICardElement(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, Size size, std::wstring speak) : m_container(container), m_horizontalAlignment(horizontalAlignment), m_size(size), m_speak(speak) {}

    std::shared_ptr<Container> ICardElement::GetContainer() const
    {
        return m_container.lock();
    }

    HorizontalAlignment ICardElement::GetHorizontalAlignment() const
    {
        return m_horizontalAlignment;
    }

    void ICardElement::SetHorizontalAlignment(const HorizontalAlignment value)
    {
        m_horizontalAlignment = value;
    }

    Size ICardElement::GetSize() const
    {
        return m_size;
    }

    void ICardElement::SetSize(const Size value)
    {
        m_size = value;
    }

    std::wstring ICardElement::GetSpeak() const
    {
        return m_speak;
    }

    void ICardElement::SetSpeak(const std::wstring value)
    {
        m_speak = value;
    }

}

