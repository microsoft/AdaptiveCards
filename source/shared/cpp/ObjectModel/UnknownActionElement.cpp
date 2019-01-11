#include "pch.h"
#include "UnknownActionElement.h"

using namespace AdaptiveSharedNamespace;

UnknownActionElement::UnknownActionElement() : BaseActionElement(ActionType::UnknownAction)
{
}

std::shared_ptr<BaseActionElement> UnknownActionElementParser::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<UnknownActionElement> unknown = BaseActionElement::Deserialize<UnknownActionElement>(json);
    unknown->SetElementTypeString(std::move(ParseUtil::GetTypeAsString(json)));
    return unknown;
}
