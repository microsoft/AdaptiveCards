#include "BaseInputElement.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

BaseInputElement::BaseInputElement(CardElementType elementType) :
    BaseCardElement(elementType)
{
}

BaseInputElement::BaseInputElement(CardElementType elementType, Spacing spacing, bool separator) :
    BaseCardElement(elementType, spacing, separator)
{
}

std::string BaseInputElement::GetId() const
{
    return m_id;
}

void BaseInputElement::SetId(const std::string value)
{
    m_id = value;
}

bool BaseInputElement::GetIsRequired() const
{
    return m_isRequired;
}

void BaseInputElement::SetIsRequired(const bool value)
{
    m_isRequired = value;
}

Json::Value BaseInputElement::SerializeToJsonValue()
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Id)] = GetId();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsRequired)] = GetIsRequired();

    return root;
}
