#include "pch.h"
#include "OpenUrlAction.h"
#include "ParseContext.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

OpenUrlAction::OpenUrlAction() : BaseActionElement(ActionType::OpenUrl)
{
    PopulateKnownPropertiesSet();
}

Json::Value OpenUrlAction::SerializeToJsonValue() const
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Url)] = GetUrl();

    return root;
}

std::string OpenUrlAction::GetUrl() const
{
    return m_url;
}

void OpenUrlAction::SetUrl(const std::string& value)
{
    m_url = value;
}

std::shared_ptr<BaseActionElement> OpenUrlActionParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<OpenUrlAction> openUrlAction = BaseActionElement::Deserialize<OpenUrlAction>(context, json);

    openUrlAction->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, true));

    return openUrlAction;
}

std::shared_ptr<BaseActionElement>
OpenUrlActionParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return OpenUrlActionParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void OpenUrlAction::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Url)});
}
