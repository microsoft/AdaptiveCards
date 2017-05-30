#include "OpenUrlAction.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

OpenUrlAction::OpenUrlAction() : BaseActionElement(ActionType::OpenUrl)
{
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
    return "";
}

std::string OpenUrlAction::GetUrl() const
{
    return m_url;
}

void OpenUrlAction::SetUrl(const std::string value)
{
    m_url = value;
}


