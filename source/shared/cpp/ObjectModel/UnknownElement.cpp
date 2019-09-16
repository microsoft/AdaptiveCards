// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "UnknownElement.h"
#include "ParseContext.h"
#include "ParseUtil.h"
#include "Util.h"

using namespace AdaptiveSharedNamespace;

UnknownElement::UnknownElement() : BaseCardElement(CardElementType::Unknown)
{
}

std::shared_ptr<BaseCardElement> UnknownElementParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    // A little tricky business -- We need to make sure that elements with unknown types [de]serialize with the same
    // type they came in with. e.g. "type": "MyCoolElement" yields an UnknownElement object, but still emits
    // "MyCoolElement" when serialized back to json. Here we get the real type string, let
    // BaseCardElement::Deserialize() do its work, then put the real string back with SetElementTypeString (otherwise,
    // the string will be initialized as "Unknown").
    std::string actualType = ParseUtil::GetTypeAsString(json);
    std::shared_ptr<UnknownElement> unknown = BaseCardElement::Deserialize<UnknownElement>(context, json);
    unknown->SetAdditionalProperties(json);
    unknown->SetElementTypeString(actualType);

    return unknown;
}

std::shared_ptr<BaseCardElement>
UnknownElementParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return UnknownElementParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

Json::Value UnknownElement::SerializeToJsonValue() const
{
    return GetAdditionalProperties();
}
