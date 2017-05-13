#include "AdaptiveCard.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

AdaptiveCard::AdaptiveCard()
{
}

AdaptiveCard::AdaptiveCard(std::string title, std::string description1, std::string description2, std::shared_ptr<Container> root) : m_title(title), m_description1(description1), m_description2(description2), m_root(root) {}

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

    // Parse body
    auto body = Container::Deserialize(json);

    // Parse targets

    // Parse actions

    auto result = std::make_shared<AdaptiveCard>();
    result->SetRoot(body);

    return result;
}

std::string AdaptiveCard::GetTitle() const
{
    return m_title;
}

void AdaptiveCards::AdaptiveCard::SetTitle(const std::string value)
{
    m_title = value;
}

std::string AdaptiveCard::GetDescription1() const
{
    return m_description1;
}

void AdaptiveCards::AdaptiveCard::SetDescription1(const std::string value)
{
    m_description1 = value;
}

std::string AdaptiveCard::GetDescription2() const
{
    return m_description2;
}

void AdaptiveCards::AdaptiveCard::SetDescription2(const std::string value)
{
    m_description2 = value;
}

std::shared_ptr<Container> AdaptiveCard::GetRoot()
{
    return m_root;
}

void AdaptiveCards::AdaptiveCard::SetRoot(std::shared_ptr<Container> value)
{
    m_root = value;
}

const CardElementType AdaptiveCards::AdaptiveCard::GetElementType() const
{
    return CardElementType::AdaptiveCard;
}

