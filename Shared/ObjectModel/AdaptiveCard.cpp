#include "AdaptiveCard.h"
#include "ACParser.h"
#include <fstream>

namespace AdaptiveCards
{

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
    return result;
}

std::string AdaptiveCard::GetTitle() const
{
    return m_title;
}

std::string AdaptiveCard::GetDescription1() const
{
    return m_description1;
}

std::string AdaptiveCard::GetDescription2() const
{
    return m_description2;
}

const Container* AdaptiveCard::GetRoot() const
{
    return m_root.get();
}

};

