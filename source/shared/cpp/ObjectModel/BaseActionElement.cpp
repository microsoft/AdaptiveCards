#include "BaseActionElement.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

BaseActionElement::BaseActionElement(
    ActionType type,
    std::string speak) :
    m_type(type),
    m_speak(speak)
{
}

BaseActionElement::BaseActionElement(ActionType type) :
    m_type(type), 
    m_speak("")
{
}

AdaptiveCards::BaseActionElement::~BaseActionElement()
{
}

std::string BaseActionElement::GetSpeak() const
{
    return m_speak;
}

void BaseActionElement::SetSpeak(const std::string value)
{
    m_speak = value;
}

std::string BaseActionElement::GetTitle() const
{
    return m_title;
}

void BaseActionElement::SetTitle(const std::string value)
{
    m_title = value;
}

const ActionType AdaptiveCards::BaseActionElement::GetElementType() const
{
    return m_type;
}

Json::Value BaseActionElement::SerializeToJsonValue()
{
    Json::Value root;
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = ActionTypeToString(GetElementType());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Speak)] = GetSpeak();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title)] = GetTitle();
    return root;
}

