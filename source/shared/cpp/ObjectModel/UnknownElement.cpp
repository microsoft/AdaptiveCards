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
    unknown->SetAdditionalProperties(json);
    unknown->SetElementTypeString(std::move(ParseUtil::GetTypeAsString(json)));
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
