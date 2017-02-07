#include "AdaptiveCard.h"
#include "ACParser.h"
#include <fstream>

using namespace AdaptiveCards;

AdaptiveCard::AdaptiveCard()
{
}

AdaptiveCard::AdaptiveCard(std::string title, std::string description1, std::string description2, std::shared_ptr<Container> root) : m_title(title), m_description1(description1), m_description2(description2), m_root(root) {}

std::shared_ptr<AdaptiveCard> AdaptiveCard::DeserializeFromFile(const std::string & jsonFile)
{
    std::ifstream in(jsonFile);

    Json::Value root;
    in >> root;

    return AdaptiveCard::Deserialize(root);
}

std::shared_ptr<AdaptiveCard> AdaptiveCard::Deserialize(const Json::Value& json)
{
    ACParser::ThrowIfNotJsonObject(json);

    // Verify this is an adaptive card
    ACParser::ExpectTypeString(json, CardElementType::AdaptiveCardType);

    // Parse body
    auto bodies = Container::Deserialize(json);

    // Parse targets

    // Parse actions

    auto result = std::make_shared<AdaptiveCard>();
    result->SetRoot(bodies);

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

