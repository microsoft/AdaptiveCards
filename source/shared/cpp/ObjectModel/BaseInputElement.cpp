// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "BaseInputElement.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

BaseInputElement::BaseInputElement() : BaseCardElement(CardElementType::Custom), m_isRequired(false)
{
    PopulateKnownPropertiesSet();
}

BaseInputElement::BaseInputElement(CardElementType elementType) : BaseCardElement(elementType), m_isRequired(false)
{
    PopulateKnownPropertiesSet();
}

BaseInputElement::BaseInputElement(CardElementType elementType, Spacing spacing, bool separator, HeightType height) :
    BaseCardElement(elementType, spacing, separator, height), m_isRequired(false)
{
    PopulateKnownPropertiesSet();
}

std::string BaseInputElement::GetLabel() const
{
    return m_label;
}

void BaseInputElement::SetLabel(const std::string label)
{
    m_label = label;
}

bool BaseInputElement::GetIsRequired() const
{
    return m_isRequired;
}

void BaseInputElement::SetIsRequired(const bool value)
{
    m_isRequired = value;
}

std::string BaseInputElement::GetErrorMessage() const
{
    return m_errorMessage;
}

void BaseInputElement::SetErrorMessage(const std::string errorMessage)
{
    m_errorMessage = errorMessage;
}

Json::Value BaseInputElement::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    if (m_isRequired)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsRequired)] = m_isRequired;
    }

    if (!m_errorMessage.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ErrorMessage)] = m_errorMessage;
    }

    if (!m_label.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Label)] = m_label;
    }

    return root;
}

void BaseInputElement::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsRequired),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ErrorMessage),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Label)});
}

std::shared_ptr<BaseInputElement> BaseInputElement::DeserializeBasePropertiesFromString(ParseContext& context, const std::string& jsonString)
{
    return BaseInputElement::DeserializeBaseProperties(context, ParseUtil::GetJsonValueFromString(jsonString));
}

std::shared_ptr<BaseInputElement> BaseInputElement::DeserializeBaseProperties(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<BaseInputElement> baseInputElement = BaseCardElement::Deserialize<BaseInputElement>(context, json);
    DeserializeBaseProperties(context, json, baseInputElement);
    return baseInputElement;
}

void BaseInputElement::DeserializeBaseProperties(ParseContext& /*context*/, const Json::Value& json, std::shared_ptr<BaseInputElement>& element)
{
    ParseUtil::ThrowIfNotJsonObject(json);

    element->SetId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Id, true));
    element->SetIsRequired(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsRequired, false));
    element->SetErrorMessage(ParseUtil::GetString(json, AdaptiveCardSchemaKey::ErrorMessage));
    element->SetLabel(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Label));
}
