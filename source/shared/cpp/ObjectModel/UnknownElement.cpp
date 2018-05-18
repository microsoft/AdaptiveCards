#include "pch.h"
#include <iomanip>
#include <regex>
#include <iostream>
#include <codecvt>
#include "UnknownElement.h"
#include "DateTimePreparser.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

UnknownElement::UnknownElement() :
    BaseCardElement(CardElementType::Unknown)
{
}

std::shared_ptr<BaseCardElement> UnknownElementParser::Deserialize(
    std::shared_ptr<ElementParserRegistration>,
    std::shared_ptr<ActionParserRegistration>,
    const Json::Value& json)
{
    std::shared_ptr<UnknownElement> unknown = BaseCardElement::Deserialize<UnknownElement>(json);
    return unknown;
}

std::shared_ptr<BaseCardElement> UnknownElementParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return UnknownElementParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}
