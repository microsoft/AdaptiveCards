#include "OpenUrlAction.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

OpenUrlAction::OpenUrlAction() : BaseActionElement(ActionType::OpenUrl)
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Url));
}

std::shared_ptr<OpenUrlAction> OpenUrlAction::Deserialize(const Json::Value& json)
{
    std::shared_ptr<OpenUrlAction> openUrlAction = BaseActionElement::Deserialize<OpenUrlAction>(json);

    openUrlAction->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, true));

    return openUrlAction;
}

std::shared_ptr<OpenUrlAction> OpenUrlAction::DeserializeFromString(const std::string& jsonString)
{
    return OpenUrlAction::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string OpenUrlAction::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value OpenUrlAction::SerializeToJsonValue()
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Url)] = GetUrl();

    return root;
}

std::string OpenUrlAction::GetUrl() const
{
    return m_url;
}

void OpenUrlAction::SetUrl(const std::string value)
{
    m_url = value;
}


