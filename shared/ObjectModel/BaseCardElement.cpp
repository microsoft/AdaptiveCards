#include "BaseCardElement.h"
#include "ACParser.h"

using namespace AdaptiveCards;

BaseCardElement::BaseCardElement(CardElementType type, std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, Size size, std::string speak) : m_type(type), m_container(container), m_horizontalAlignment(horizontalAlignment), m_size(size), m_speak(speak) {}

BaseCardElement::BaseCardElement(CardElementType type) : m_type(type), m_horizontalAlignment(HorizontalAlignment::Left), m_size(Size::Auto) {}

std::shared_ptr<Container> BaseCardElement::GetContainer() const
{
    return m_container.lock();
}

void BaseCardElement::SetContainer(std::shared_ptr<Container> container)
{
    m_container = container;
}

HorizontalAlignment BaseCardElement::GetHorizontalAlignment() const
{
    return m_horizontalAlignment;
}

void BaseCardElement::SetHorizontalAlignment(const HorizontalAlignment value)
{
    m_horizontalAlignment = value;
}

Size BaseCardElement::GetSize() const
{
    return m_size;
}

void BaseCardElement::SetSize(const Size value)
{
    m_size = value;
}

std::string BaseCardElement::GetSpeak() const
{
    return m_speak;
}

void BaseCardElement::SetSpeak(const std::string value)
{
    m_speak = value;
}

const CardElementType AdaptiveCards::BaseCardElement::GetElementType() const
{
    return m_type;
}

