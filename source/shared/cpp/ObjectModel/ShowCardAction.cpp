#include "pch.h"
#include "SharedAdaptiveCard.h"
#include "ParseUtil.h"
#include "ShowCardAction.h"
#include "ParseContext.h"

using namespace AdaptiveSharedNamespace;

ShowCardAction::ShowCardAction() : BaseActionElement(ActionType::ShowCard)
{
    PopulateKnownPropertiesSet();
}

Json::Value ShowCardAction::SerializeToJsonValue() const
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Card)] = GetCard()->SerializeToJsonValue();

    return root;
}

std::shared_ptr<AdaptiveCard> ShowCardAction::GetCard() const
{
    return m_card;
}

void ShowCardAction::SetCard(const std::shared_ptr<AdaptiveCard> card)
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

std::shared_ptr<BaseActionElement> ShowCardActionParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<ShowCardAction> showCardAction = BaseActionElement::Deserialize<ShowCardAction>(context, json);

    std::string propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Card);

    auto parseResult = AdaptiveCard::Deserialize(json.get(propertyName, Json::Value()), "", context);

    auto showCardWarnings = parseResult->GetWarnings();
    auto warningsEnd = context.warnings.insert(context.warnings.end(), showCardWarnings.begin(), showCardWarnings.end());

    showCardAction->SetCard(parseResult->GetAdaptiveCard());

    return showCardAction;
}

std::shared_ptr<BaseActionElement>
ShowCardActionParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ShowCardActionParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void ShowCardAction::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Card)});
}

void ShowCardAction::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    auto card = GetCard();
    auto showCardResources = card->GetResourceInformation();
    auto resourceInfoEnd = resourceInfo.insert(resourceInfo.end(), showCardResources.begin(), showCardResources.end());
    return;
}
