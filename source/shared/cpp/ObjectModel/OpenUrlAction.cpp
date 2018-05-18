#include "pch.h"
#include "OpenUrlAction.h"
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

void OpenUrlAction::SetUrl(const std::string &value)
{
    m_url = value;
}

std::shared_ptr<BaseActionElement> OpenUrlActionParser::Deserialize(
    std::shared_ptr<ElementParserRegistration>,
    std::shared_ptr<ActionParserRegistration>,
    const Json::Value& json)
{
    std::shared_ptr<OpenUrlAction> openUrlAction = BaseActionElement::Deserialize<OpenUrlAction>(json);

    openUrlAction->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, true));

    return openUrlAction;
}

std::shared_ptr<BaseActionElement> OpenUrlActionParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return OpenUrlActionParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}

void OpenUrlAction::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Url));
}
