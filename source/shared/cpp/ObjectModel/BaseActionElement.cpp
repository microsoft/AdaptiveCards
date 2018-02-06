#include "BaseActionElement.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

BaseActionElement::BaseActionElement(ActionType type) :
    m_type(type)
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Id));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title));
}

AdaptiveCards::BaseActionElement::~BaseActionElement()
{
}

std::string BaseActionElement::GetTitle() const
{
    return m_title;
}

void BaseActionElement::SetTitle(const std::string value)
{
    m_title = value;
}

std::string BaseActionElement::GetId() const
{
    return m_id;
}

void BaseActionElement::SetId(const std::string value)
{
    m_id = value;
}

const ActionType AdaptiveCards::BaseActionElement::GetElementType() const
{
    return m_type;
}

std::string BaseActionElement::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value BaseActionElement::SerializeToJsonValue()
{
    Json::Value root;
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = ActionTypeToString(GetElementType());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title)] = GetTitle();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Id)] = GetId();
    return root;
}

Json::Value BaseActionElement::GetAdditionalProperties()
{
    return m_additionalProperties;
}

void BaseActionElement::SetAdditionalProperties(Json::Value value)
{
    m_additionalProperties = value;
}
