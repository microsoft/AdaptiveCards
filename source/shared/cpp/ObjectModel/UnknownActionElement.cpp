#include "pch.h"
#include "UnknownActionElement.h"

using namespace AdaptiveSharedNamespace;

UnknownActionElement::UnknownActionElement() : BaseActionElement(ActionType::UnknownAction)
{
}

std::shared_ptr<BaseActionElement> UnknownActionElementParser::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<UnknownActionElement> unknown = std::make_shared<UnknownActionElement>();
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
