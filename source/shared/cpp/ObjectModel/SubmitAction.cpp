#include "pch.h"
#include "ParseUtil.h"
#include "SubmitAction.h"

using namespace AdaptiveSharedNamespace;

SubmitAction::SubmitAction() : BaseActionElement(ActionType::Submit)
{
    PopulateKnownPropertiesSet();
}

std::string SubmitAction::GetDataJson() const
{
    return m_dataJson;
}

void SubmitAction::SetDataJson(const std::string value)
{
    m_dataJson = value;
}

Json::Value SubmitAction::SerializeToJsonValue()
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Data)] = GetDataJson();

    return root;
}


std::shared_ptr<BaseActionElement> SubmitActionParser::Deserialize(
    std::shared_ptr<ElementParserRegistration>,
    std::shared_ptr<ActionParserRegistration>,
    const Json::Value& json)
{
    std::shared_ptr<SubmitAction> submitAction = BaseActionElement::Deserialize<SubmitAction>(json);

    submitAction->SetDataJson(ParseUtil::GetJsonString(json, AdaptiveCardSchemaKey::Data));

    return submitAction;
}

std::shared_ptr<BaseActionElement> SubmitActionParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return SubmitActionParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}

void SubmitAction::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Data));
}
