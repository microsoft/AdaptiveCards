#pragma once

#include <vector>
#include <memory>
#include "enums.h"
#include "ACParser.h"

namespace AdaptiveCards
{
class ICardElement;

class Container
{
public:
    ~Container() {};
    std::vector<std::shared_ptr<ICardElement>>& GetItems();

    static std::shared_ptr<Container> Deserialize(const Json::Value& root);

private:
    std::vector<std::shared_ptr<AdaptiveCards::ICardElement>> m_items;
    TextColor m_textColor;
};
}