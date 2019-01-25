#include "pch.h"
#include "UnknownActionElement.h"

using namespace AdaptiveSharedNamespace;

UnknownActionElement::UnknownActionElement() : BaseActionElement(ActionType::UnknownAction)
{
}

Json::Value AdaptiveSharedNamespace::UnknownActionElement::SerializeToJsonValue() const
{
    return GetAdditionalProperties();
}

std::shared_ptr<BaseActionElement> UnknownActionElementParser::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<UnknownActionElement> unknown = std::make_shared<UnknownActionElement>();
    unknown->SetAdditionalProperties(json);
    unknown->SetElementTypeString(std::move(ParseUtil::GetTypeAsString(json)));
    return unknown;
}
