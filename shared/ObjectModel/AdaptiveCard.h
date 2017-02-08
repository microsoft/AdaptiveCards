#pragma once

#include "Enums.h"
#include "BaseCardElement.h"
#include "Container.h"
#include "pch.h"

namespace AdaptiveCards
{
class Container;

class AdaptiveCard
{
public:
    AdaptiveCard();
    AdaptiveCard(std::string title, std::string description1, std::string description2, std::shared_ptr<Container> root);

    std::string GetTitle() const;
    void SetTitle(const std::string value);
    std::string GetDescription1() const;
    void SetDescription1(const std::string value);
    std::string GetDescription2() const;
    void SetDescription2(const std::string value);
    std::shared_ptr<Container> GetRoot();
    void SetRoot(std::shared_ptr<Container> value);

    const CardElementType GetElementType() const;

    static std::shared_ptr<AdaptiveCard> DeserializeFromFile(const std::string & jsonFile);
    static std::shared_ptr<AdaptiveCard> Deserialize(const Json::Value& json);

private:

    std::string m_title;
    std::string m_description1;
    std::string m_description2;
    std::shared_ptr<Container> m_root;

};
}