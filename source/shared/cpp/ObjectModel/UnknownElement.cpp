#include "pch.h"
#include <iomanip>
#include <regex>
#include <iostream>
#include <codecvt>
#include "UnknownElement.h"
#include "DateTimePreparser.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

UnknownElement::UnknownElement() : BaseCardElement(CardElementType::Unknown)
{
}

std::shared_ptr<BaseCardElement> UnknownElementParser::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<UnknownElement> unknown = std::make_shared<UnknownElement>();
    Json::Value additionalProperties = unknown->GetAdditionalProperties();
    for (auto it = json.begin(); it != json.end(); ++it)
    {
        std::string key = it.key().asCString();
        additionalProperties[key] = *it;
    }
    unknown->SetElementTypeString(std::move(ParseUtil::GetTypeAsString(json)));
    unknown->SetAdditionalProperties(additionalProperties);
    return unknown;
}

std::shared_ptr<BaseCardElement>
UnknownElementParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return UnknownElementParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
