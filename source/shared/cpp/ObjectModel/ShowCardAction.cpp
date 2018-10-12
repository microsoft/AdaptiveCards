#include "pch.h"
#include "SharedAdaptiveCard.h"
#include "ParseUtil.h"
#include "ShowCardAction.h"

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

std::shared_ptr<BaseActionElement> ShowCardActionParser::Deserialize(std::shared_ptr<ElementParserRegistration> elementParserRegistration,
                                                                     std::shared_ptr<ActionParserRegistration> actionParserRegistration,
                                                                     std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
                                                                     const Json::Value& json)
{
    std::shared_ptr<ShowCardAction> showCardAction = BaseActionElement::Deserialize<ShowCardAction>(json);

    std::string propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Card);

    auto parseResult =
        AdaptiveCard::Deserialize(json.get(propertyName, Json::Value()), "", elementParserRegistration, actionParserRegistration);

    auto showCardWarnings = parseResult->GetWarnings();
    auto warningsEnd = warnings.insert(warnings.end(), showCardWarnings.begin(), showCardWarnings.end());

    showCardAction->SetCard(parseResult->GetAdaptiveCard());

    return showCardAction;
}

std::shared_ptr<BaseActionElement>
ShowCardActionParser::DeserializeFromString(std::shared_ptr<ElementParserRegistration> elementParserRegistration,
                                            std::shared_ptr<ActionParserRegistration> actionParserRegistration,
                                            std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
                                            const std::string& jsonString)
{
    return ShowCardActionParser::Deserialize(elementParserRegistration,
                                             actionParserRegistration,
                                             warnings,
                                             ParseUtil::GetJsonValueFromString(jsonString));
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
