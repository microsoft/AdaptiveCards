#include "SharedAdaptiveCard.h"
#include "ParseUtil.h"
#include "ShowCardAction.h"

using namespace AdaptiveCards;

ShowCardAction::ShowCardAction() : BaseActionElement(ActionType::ShowCard)
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Card));
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

void ShowCardAction::SetLanguage(const std::string& value)
{
    // If the card inside doesn't specify language, propagate
    if (m_card->GetLanguage().empty())
    {
        m_card->SetLanguage(value);
    }
}

std::shared_ptr<BaseActionElement> ShowCardActionParser::Deserialize(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const Json::Value& json)
{
    std::shared_ptr<ShowCardAction> showCardAction = BaseActionElement::Deserialize<ShowCardAction>(json);

    std::string propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Card);
    showCardAction->SetCard(AdaptiveCard::Deserialize(json.get(propertyName, Json::Value()), elementParserRegistration, actionParserRegistration));

    return showCardAction;
}

std::shared_ptr<BaseActionElement> ShowCardActionParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return ShowCardActionParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}

