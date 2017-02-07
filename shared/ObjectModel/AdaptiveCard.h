#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ICardElement.h"
#include "json\json.h"

namespace AdaptiveCards
{
class Container;

class AdaptiveCard
{
public:
    AdaptiveCard();
    AdaptiveCard(std::string title, std::string description1, std::string description2, std::shared_ptr<Container> root);

    std::string GetTitle() const;
    std::string GetDescription1() const;
    std::string GetDescription2() const;

    const Container* GetRoot() const;

    static std::shared_ptr<AdaptiveCard> DeserializeFromFile(const std::string & jsonFile);
    static std::shared_ptr<AdaptiveCard> Deserialize(const Json::Value& json);

private:

    std::string m_title;
    std::string m_description1;
    std::string m_description2;
    std::shared_ptr<Container> m_root;

};
}