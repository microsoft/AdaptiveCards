#include "ParseUtil.h"
#include "ShowCardAction.h"

using namespace AdaptiveCards;

ShowCardAction::ShowCardAction() : BaseActionElement(ActionType::ShowCard)
{
}

std::shared_ptr<ShowCardAction> ShowCardAction::Deserialize(const Json::Value& json)
{
    std::shared_ptr<ShowCardAction> showCardAction = BaseActionElement::Deserialize<ShowCardAction>(json);

    showCardAction->SetTitle(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Title));

    return showCardAction;
}

std::shared_ptr<ShowCardAction> ShowCardAction::DeserializeFromString(const std::string& jsonString)
{
    Json::Value jsonValue(jsonString);

    return ShowCardAction::Deserialize(jsonValue);
}

std::string ShowCardAction::Serialize()
{
    return "";
}

std::string ShowCardAction::GetTitle() const
{
    return m_title;
}

void ShowCardAction::SetTitle(const std::string value)
{
    m_title = value;
}