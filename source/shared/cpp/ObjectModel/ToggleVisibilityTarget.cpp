// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ParseUtil.h"
#include "ToggleVisibilityTarget.h"

using namespace AdaptiveSharedNamespace;

ToggleVisibilityTarget::ToggleVisibilityTarget() : m_visibilityToggle(IsVisibleToggle)
{
}

std::string ToggleVisibilityTarget::GetElementId() const
{
    return m_targetId;
}

void ToggleVisibilityTarget::SetElementId(const std::string& value)
{
    m_targetId = value;
}

IsVisible ToggleVisibilityTarget::GetIsVisible() const
{
    return m_visibilityToggle;
}

void ToggleVisibilityTarget::SetIsVisible(IsVisible value)
{
    m_visibilityToggle = value;
}

std::shared_ptr<ToggleVisibilityTarget> ToggleVisibilityTarget::Deserialize(ParseContext&, const Json::Value& json)
{
    auto toggleVisibilityTargetElement = std::make_shared<ToggleVisibilityTarget>();

    if (json.isString())
    {
        toggleVisibilityTargetElement->SetElementId(json.asString());
    }
    else
    {
        toggleVisibilityTargetElement->SetElementId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::ElementId, true));

        auto propertyValue = json.get(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsVisible), Json::Value());
        if (!propertyValue.empty())
        {
            if (!propertyValue.isBool())
            {
                throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                 "Value for property " +
                                                     AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsVisible) +
                                                     " was invalid. Expected type bool.");
            }

            toggleVisibilityTargetElement->SetIsVisible(propertyValue.asBool() ? IsVisibleTrue : IsVisibleFalse);
        }
    }

    return toggleVisibilityTargetElement;
}

std::shared_ptr<ToggleVisibilityTarget> ToggleVisibilityTarget::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ToggleVisibilityTarget::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

std::string ToggleVisibilityTarget::Serialize()
{
    return ParseUtil::JsonToString(SerializeToJsonValue());
}

Json::Value ToggleVisibilityTarget::SerializeToJsonValue()
{
    const auto visibilityToggle = GetIsVisible();
    if (visibilityToggle == IsVisibleToggle)
    {
        // If this is a toggle target, return just a json string
        return Json::Value(GetElementId());
    }
    else
    {
        // For true and false targets return a json object with a "targetId" and "isVisible" properties
        Json::Value root;
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ElementId)] = GetElementId();
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsVisible)] = (visibilityToggle == IsVisibleTrue);
        return root;
    }
}
