#include "ParseUtil.h"
#include "SubmitAction.h"

using namespace AdaptiveCards;

SubmitAction::SubmitAction() : BaseActionElement(ActionType::Submit)
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Data));
}

std::string SubmitAction::GetDataJson() const
{
    return m_dataJson;
}

void SubmitAction::SetDataJson(const std::string value)
{
    m_dataJson = value;
}

std::shared_ptr<SubmitAction> SubmitAction::Deserialize(const Json::Value& json)
{
    std::shared_ptr<SubmitAction> submitAction = BaseActionElement::Deserialize<SubmitAction>(json);

    submitAction->SetDataJson(ParseUtil::GetJsonString(json, AdaptiveCardSchemaKey::Data));

    return submitAction;
}

std::shared_ptr<SubmitAction> SubmitAction::DeserializeFromString(const std::string& jsonString)
{
    return SubmitAction::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string SubmitAction::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value SubmitAction::SerializeToJsonValue()
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Data)] = GetDataJson();

    return root;
}



