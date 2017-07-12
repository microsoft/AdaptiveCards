#include "SharedAdaptiveCard.h"
#include "ParseUtil.h"
#include "ShowCardAction.h"

using namespace AdaptiveCards;

ShowCardAction::ShowCardAction() : BaseActionElement(ActionType::ShowCard)
{
}

std::shared_ptr<ShowCardAction> ShowCardAction::Deserialize(const Json::Value& json)
{
    std::shared_ptr<ShowCardAction> showCardAction = BaseActionElement::Deserialize<ShowCardAction>(json);

    std::string propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Card);
    showCardAction->SetCard(AdaptiveCard::Deserialize(json.get(propertyName, Json::Value())));

    return showCardAction;
}

std::shared_ptr<ShowCardAction> ShowCardAction::DeserializeFromString(const std::string& jsonString)
{
    return ShowCardAction::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string ShowCardAction::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value ShowCardAction::SerializeToJsonValue()
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Card)] = GetCard()->SerializeToJsonValue();

    return root;
}

std::shared_ptr<AdaptiveCard> AdaptiveCards::ShowCardAction::GetCard() const
{
    return m_card;
}

void AdaptiveCards::ShowCardAction::SetCard(const std::shared_ptr<AdaptiveCard> card)
{
    m_card = card;
}
