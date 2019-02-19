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
