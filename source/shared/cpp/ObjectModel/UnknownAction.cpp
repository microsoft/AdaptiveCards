// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "UnknownAction.h"

using namespace AdaptiveSharedNamespace;

UnknownAction::UnknownAction() : BaseActionElement(ActionType::UnknownAction)
{
}

Json::Value AdaptiveSharedNamespace::UnknownAction::SerializeToJsonValue() const
{
    return GetAdditionalProperties();
}

std::shared_ptr<BaseActionElement> UnknownActionParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::string actualType = ParseUtil::GetTypeAsString(json);
    std::shared_ptr<UnknownAction> unknown = BaseActionElement::Deserialize<UnknownAction>(context, json);
    unknown->SetAdditionalProperties(json);
    unknown->SetElementTypeString(actualType);
    return unknown;
}

std::shared_ptr<BaseActionElement>
UnknownActionParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return UnknownActionParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
