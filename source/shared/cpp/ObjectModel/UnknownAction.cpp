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

std::shared_ptr<BaseActionElement> UnknownActionParser::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<UnknownAction> unknown = std::make_shared<UnknownAction>();
    unknown->SetAdditionalProperties(json);
    unknown->SetElementTypeString(std::move(ParseUtil::GetTypeAsString(json)));
    return unknown;
}
