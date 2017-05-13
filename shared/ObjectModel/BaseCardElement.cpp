#include "BaseCardElement.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

BaseCardElement::BaseCardElement(
    CardElementType type,
    std::shared_ptr<Container> parent,
    HorizontalAlignment horizontalAlignment,
    CardElementSize size,
    std::string speak) :
    m_type(type),
    m_parent(parent),
    m_horizontalAlignment(horizontalAlignment),
    m_size(size),
    m_speak(speak)
{
}

BaseCardElement::BaseCardElement(CardElementType type) :
    m_type(type), m_horizontalAlignment(HorizontalAlignment::Left), m_size(CardElementSize::Auto), m_speak("")
{
}

AdaptiveCards::BaseCardElement::~BaseCardElement()
{
}

std::shared_ptr<Container> BaseCardElement::GetParent() const
{
    return m_parent.lock();
}

void BaseCardElement::SetContainer(std::shared_ptr<Container> container)
{
    m_parent = container;
}

HorizontalAlignment BaseCardElement::GetHorizontalAlignment() const
{
    return m_horizontalAlignment;
}

void BaseCardElement::SetHorizontalAlignment(const HorizontalAlignment value)
{
    m_horizontalAlignment = value;
}

CardElementSize BaseCardElement::GetSize() const
{
    return m_size;
}

void BaseCardElement::SetSize(const CardElementSize value)
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

