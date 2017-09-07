#include "SharedAdaptiveCard.h"
#include "ChoiceSetInput.h"
#include "ColumnSet.h"
#include "Container.h"
#include "DateInput.h"
#include "FactSet.h"
#include "HttpAction.h"
#include "Image.h"
#include "ImageSet.h"
#include "NumberInput.h"
#include "OpenUrlAction.h"
#include "ParseUtil.h"
#include "ShowCardAction.h"
#include "SubmitAction.h"
#include "TextBlock.h"
#include "TextInput.h"
#include "TimeInput.h"
#include "ToggleInput.h"

using namespace AdaptiveCards;

const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, EnumHash> AdaptiveCard::CardElementParsers =
{
    { CardElementType::Container, Container::Deserialize },
    { CardElementType::ColumnSet, ColumnSet::Deserialize },
    { CardElementType::FactSet, FactSet::Deserialize },
    { CardElementType::Image, Image::Deserialize },
    { CardElementType::ImageSet, ImageSet::Deserialize },
    { CardElementType::TextBlock, TextBlock::Deserialize },
    { CardElementType::ChoiceSetInput, ChoiceSetInput::Deserialize },
    { CardElementType::DateInput, DateInput::Deserialize },
    { CardElementType::NumberInput, NumberInput::Deserialize },
    { CardElementType::TextInput, TextInput::Deserialize },
    { CardElementType::TimeInput, TimeInput::Deserialize },
    { CardElementType::ToggleInput, ToggleInput::Deserialize },
};

const std::unordered_map<ActionType, std::function<std::shared_ptr<BaseActionElement>(const Json::Value&)>, EnumHash> AdaptiveCard::ActionParsers =
{
    { ActionType::Http, HttpAction::Deserialize },
    { ActionType::OpenUrl, OpenUrlAction::Deserialize },
    { ActionType::ShowCard, ShowCardAction::Deserialize },
    { ActionType::Submit, SubmitAction::Deserialize },
};

AdaptiveCard::AdaptiveCard()
{
}

AdaptiveCard::AdaptiveCard(std::string version,
    std::string minVersion,
    std::string fallbackText,
    std::string backgroundImage,
    std::string speak) :
    m_version(version),
    m_minVersion(minVersion),
    m_fallbackText(fallbackText),
    m_backgroundImage(backgroundImage),
    m_speak(speak)
{
}

AdaptiveCard::AdaptiveCard(std::string version,
    std::string minVersion,
    std::string fallbackText,
    std::string backgroundImage,
    std::string speak,
    std::vector<std::shared_ptr<BaseCardElement>>& body, std::vector<std::shared_ptr<BaseActionElement>>& actions) :
    m_version(version),
    m_minVersion(minVersion),
    m_fallbackText(fallbackText),
    m_backgroundImage(backgroundImage),
    m_speak(speak),
    m_body(body),
    m_actions(actions)
{
}

std::shared_ptr<AdaptiveCard> AdaptiveCard::DeserializeFromFile(const std::string& jsonFile) throw (AdaptiveCards::AdaptiveCardParseException)
{
    std::ifstream jsonFileStream(jsonFile);

    Json::Value root;
    jsonFileStream >> root;

    return AdaptiveCard::Deserialize(root);
}

std::shared_ptr<AdaptiveCard> AdaptiveCard::Deserialize(const Json::Value& json) throw(AdaptiveCards::AdaptiveCardParseException)
{
    ParseUtil::ThrowIfNotJsonObject(json);

    // Verify this is an adaptive card
    ParseUtil::ExpectTypeString(json, CardElementType::AdaptiveCard);

    std::string version = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Version);
    std::string minVersion = ParseUtil::GetString(json, AdaptiveCardSchemaKey::MinVersion);
    std::string fallbackText = ParseUtil::GetString(json, AdaptiveCardSchemaKey::FallbackText);
    std::string backgroundImageUrl = ParseUtil::GetString(json, AdaptiveCardSchemaKey::BackgroundImageUrl);
    std::string backgroundImage = backgroundImageUrl != "" ? backgroundImageUrl :
        ParseUtil::GetString(json, AdaptiveCardSchemaKey::BackgroundImage);
    std::string speak = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Speak);

    // Parse body
    auto body = ParseUtil::GetElementCollection<BaseCardElement>(json, AdaptiveCardSchemaKey::Body, AdaptiveCard::CardElementParsers, false);

    // Parse actions if present
    auto actions = ParseUtil::GetActionCollection<BaseActionElement>(json, AdaptiveCardSchemaKey::Actions, AdaptiveCard::ActionParsers);

    auto result = std::make_shared<AdaptiveCard>(version, minVersion, fallbackText, backgroundImage, speak, body, actions);
    return result;
}

Json::Value AdaptiveCard::SerializeToJsonValue()
{
    Json::Value root;
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = CardElementTypeToString(CardElementType::AdaptiveCard);
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Version)] = GetVersion();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MinVersion)] = GetMinVersion();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FallbackText)] = GetFallbackText();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::BackgroundImage)] = GetBackgroundImage();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Speak)] = GetSpeak();

    std::string bodyPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Body);
    root[bodyPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : GetBody())
    {
        root[bodyPropertyName].append(cardElement->SerializeToJsonValue());
    }

    std::string actionsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Actions);
    root[actionsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& action : GetActions())
    {
        root[actionsPropertyName].append(action->SerializeToJsonValue());
    }

    return root;
}

std::string AdaptiveCard::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

std::shared_ptr<AdaptiveCard> AdaptiveCard::DeserializeFromString(const std::string& jsonString) throw(AdaptiveCards::AdaptiveCardParseException)
{
    return AdaptiveCard::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string AdaptiveCard::GetVersion() const
{
    return m_version;
}

void AdaptiveCard::SetVersion(const std::string value)
{
    m_version = value;
}

std::string AdaptiveCard::GetMinVersion() const
{
    return m_minVersion;
}

void AdaptiveCard::SetMinVersion(const std::string value)
{
    m_minVersion = value;
}

std::string AdaptiveCard::GetFallbackText() const
{
    return m_fallbackText;
}

void AdaptiveCard::SetFallbackText(const std::string value)
{
    m_fallbackText = value;
}

std::string AdaptiveCard::GetBackgroundImage() const
{
    return m_backgroundImage;
}

void AdaptiveCard::SetBackgroundImage(const std::string value)
{
    m_backgroundImage = value;
}

std::string AdaptiveCard::GetSpeak() const
{
    return m_speak;
}

void AdaptiveCard::SetSpeak(const std::string value)
{
    m_speak = value;
}

const CardElementType AdaptiveCard::GetElementType() const
{
    return CardElementType::AdaptiveCard;
}

const std::vector<std::shared_ptr<BaseCardElement>>& AdaptiveCard::GetBody() const
{
    return m_body;
}

std::vector<std::shared_ptr<BaseCardElement>>& AdaptiveCard::GetBody()
{
    return m_body;
}

const std::vector<std::shared_ptr<BaseActionElement>>& AdaptiveCard::GetActions() const
{
    return m_actions;
}
