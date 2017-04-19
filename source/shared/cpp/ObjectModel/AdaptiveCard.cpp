#include "AdaptiveCard.h"
#include "ParseUtil.h"
#include "Image.h"
#include "Container.h"
#include "TextBlock.h"
#include "ColumnSet.h"
#include "FactSet.h"
#include "ImageSet.h"

using namespace AdaptiveCards;

const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, EnumHash> AdaptiveCard::CardElementParsers =
{
    { CardElementType::Container, Container::Deserialize },
    { CardElementType::ColumnSet, ColumnSet::Deserialize },
    { CardElementType::FactSet, FactSet::Deserialize },
    { CardElementType::Image, Image::Deserialize },
    { CardElementType::ImageSet, ImageSet::Deserialize },
    { CardElementType::TextBlock, TextBlock::Deserialize },
};

AdaptiveCard::AdaptiveCard()
{
}

AdaptiveCard::AdaptiveCard(std::string version, std::string minVersion, std::string fallbackText) :
    m_version(version),
    m_minVersion(minVersion),
    m_fallbackText(fallbackText)
{
}

AdaptiveCard::AdaptiveCard(std::string version, std::string minVersion, std::string fallbackText, std::vector<std::shared_ptr<BaseCardElement>>& body) :
    m_version(version),
    m_minVersion(minVersion),
    m_fallbackText(fallbackText),
    m_body(body)
{
}

std::shared_ptr<AdaptiveCard> AdaptiveCard::DeserializeFromFile(const std::string& jsonFile)
{
    std::ifstream jsonFileStream(jsonFile);

    Json::Value root;
    jsonFileStream >> root;

    return AdaptiveCard::Deserialize(root);
}

std::shared_ptr<AdaptiveCard> AdaptiveCard::Deserialize(const Json::Value& json)
{
    ParseUtil::ThrowIfNotJsonObject(json);

    // Verify this is an adaptive card
    ParseUtil::ExpectTypeString(json, CardElementType::AdaptiveCard);

    std::string version = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Version);
    std::string minVersion = ParseUtil::GetString(json, AdaptiveCardSchemaKey::MinVersion);
    std::string fallbackText = ParseUtil::GetString(json, AdaptiveCardSchemaKey::FallbackText);

    // Parse body
    auto body = ParseUtil::GetElementCollection<BaseCardElement>(json, AdaptiveCardSchemaKey::Body, AdaptiveCard::CardElementParsers);

    // Parse actions

    auto result = std::make_shared<AdaptiveCard>(version, minVersion, fallbackText, body);
    return result;
}

std::shared_ptr<AdaptiveCard> AdaptiveCard::DeserializeFromString(const std::string& jsonString)
{
    Json::Value jsonValue(jsonString);

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
