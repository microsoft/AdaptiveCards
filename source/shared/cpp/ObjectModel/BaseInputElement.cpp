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

std::shared_ptr<BaseInputElement> BaseInputElement::ExtractBasePropertiesFromString(ParseContext& context, const std::string& jsonString)
{
    return BaseInputElement::ExtractBaseProperties(context, ParseUtil::GetJsonValueFromString(jsonString));
}

std::shared_ptr<BaseInputElement> BaseInputElement::ExtractBaseProperties(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<BaseInputElement> baseInputElement = BaseCardElement::Deserialize<BaseInputElement>(context, json);

    ParseUtil::ThrowIfNotJsonObject(json);

    baseInputElement->SetId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Id, true));
    baseInputElement->SetIsRequired(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsRequired, false));
    baseInputElement->SetErrorMessage(ParseUtil::GetString(json, AdaptiveCardSchemaKey::ErrorMessage));
    baseInputElement->SetLabel(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Label));
    
    return baseInputElement;
}
