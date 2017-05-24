#include "AdaptiveCard.h"
#include "ColumnSet.h"
#include "Container.h"
#include "FactSet.h"
#include "HttpAction.h"
#include "Image.h"
#include "ImageSet.h"
#include "InputChoiceSet.h"
#include "InputDate.h"
#include "InputNumber.h"
#include "InputText.h"
#include "InputTime.h"
#include "InputToggle.h"
#include "OpenUrlAction.h"
#include "ParseUtil.h"
#include "TextBlock.h"
#include "ShowCardAction.h"
#include "SubmitAction.h"

using namespace AdaptiveCards;

const std::unordered_map<ActionType, std::function<std::shared_ptr<BaseActionElement>(const Json::Value&)>, EnumHash> AdaptiveCard::CardActionParsers =
{
    { ActionType::Http, HttpAction::Deserialize },
    { ActionType::OpenUrl, OpenUrlAction::Deserialize },
    { ActionType::ShowCard, ShowCardAction::Deserialize },
    { ActionType::Submit, SubmitAction::Deserialize },
};

const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, EnumHash> AdaptiveCard::CardElementParsers =
{
    { CardElementType::Container, Container::Deserialize },
    { CardElementType::ColumnSet, ColumnSet::Deserialize },
    { CardElementType::FactSet, FactSet::Deserialize },
    { CardElementType::Image, Image::Deserialize },
    { CardElementType::ImageSet, ImageSet::Deserialize },
    { CardElementType::TextBlock, TextBlock::Deserialize },
    { CardElementType::InputChoiceSet, InputChoiceSet::Deserialize },
    { CardElementType::InputDate, InputDate::Deserialize },
    { CardElementType::InputNumber, InputNumber::Deserialize },
    { CardElementType::InputText, InputText::Deserialize },
    { CardElementType::InputTime, InputTime::Deserialize },
    { CardElementType::InputToggle, InputToggle::Deserialize },
};

AdaptiveCard::AdaptiveCard()
{
}

AdaptiveCard::AdaptiveCard(std::string version, std::string minVersion, std::string fallbackText, std::string backgroundImageUrl) :
    m_version(version),
    m_minVersion(minVersion),
    m_fallbackText(fallbackText),
    m_backgroundImageUrl(backgroundImageUrl)
{
}

AdaptiveCard::AdaptiveCard(std::string version, std::string minVersion, std::string fallbackText, std::string backgroundImageUrl, std::vector<std::shared_ptr<BaseCardElement>>& body, std::vector<std::shared_ptr<BaseActionElement>>& actions) :
    m_version(version),
    m_minVersion(minVersion),
    m_fallbackText(fallbackText),
    m_backgroundImageUrl(backgroundImageUrl),
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

    // Parse body
    auto body = ParseUtil::GetElementCollection<BaseCardElement>(json, AdaptiveCardSchemaKey::Body, AdaptiveCard::CardElementParsers, true);

    // Parse actions if present
    auto actions = ParseUtil::GetActionCollection<BaseActionElement>(json, AdaptiveCardSchemaKey::Actions, AdaptiveCard::CardActionParsers);

    auto result = std::make_shared<AdaptiveCard>(version, minVersion, fallbackText, backgroundImageUrl, body, actions);
    return result;
}

std::shared_ptr<AdaptiveCard> AdaptiveCard::DeserializeFromString(const std::string& jsonString) throw(AdaptiveCards::AdaptiveCardParseException)
{
    Json::Reader reader;
    Json::Value jsonValue;
    if (!reader.parse(jsonString.c_str(), jsonValue))
    {
        throw AdaptiveCardParseException("Expected JSON Object\n");
    }

    return AdaptiveCard::Deserialize(jsonValue);
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

std::string AdaptiveCard::GetBackgroundImageUrl() const
{
    return m_backgroundImageUrl;
}

void AdaptiveCard::SetBackgroundImageUrl(const std::string value)
{
    m_backgroundImageUrl = value;
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
