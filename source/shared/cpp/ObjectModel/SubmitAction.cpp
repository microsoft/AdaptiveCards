#include "ParseUtil.h"
#include "SubmitAction.h"

using namespace AdaptiveCards;

SubmitAction::SubmitAction() : BaseActionElement(ActionType::Submit)
{
}

std::shared_ptr<SubmitAction> SubmitAction::Deserialize(const Json::Value& json)
{
    std::shared_ptr<SubmitAction> submitAction = BaseActionElement::Deserialize<SubmitAction>(json);

    return submitAction;
}

std::shared_ptr<SubmitAction> SubmitAction::DeserializeFromString(const std::string& jsonString)
{
    return SubmitAction::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string SubmitAction::Serialize()
{
    return "";
}

std::string SubmitAction::GetTitle() const
{
    return m_title;
}

void SubmitAction::SetTitle(const std::string value)
{
    m_title = value;
}


