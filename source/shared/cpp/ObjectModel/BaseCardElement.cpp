#include "BaseCardElement.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

BaseCardElement::BaseCardElement(
    CardElementType type,
    SeparationStyle separationStyle,
    std::string speak) :
    m_type(type),
    m_separationStyle(separationStyle),
    m_speak(speak)
{
}

BaseCardElement::BaseCardElement(CardElementType type) :
    m_type(type), m_separationStyle(SeparationStyle::Default), m_speak("")
{
}

AdaptiveCards::BaseCardElement::~BaseCardElement()
{
}

SeparationStyle BaseCardElement::GetSeparationStyle() const
{
    return m_separationStyle;
}

void BaseCardElement::SetSeparationStyle(const SeparationStyle value)
{
    m_separationStyle = value;
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

