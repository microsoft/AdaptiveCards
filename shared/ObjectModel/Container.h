#pragma once

#include <vector>
#include <memory>
#include "ICardElement.h"
#include "enums.h"
#include "ACParser.h"

namespace AdaptiveCards
{
class ICardElement;
class Container : std::enable_shared_from_this<Container>
{
public:
    const std::vector<std::shared_ptr<ICardElement>>& GetItems();

    std::shared_ptr<ICardElement> GetItem(int index);
    void AddItem(std::shared_ptr<ICardElement> item);

    static std::shared_ptr<Container> Deserialize(const Json::Value& root);

private:
    std::vector<std::shared_ptr<AdaptiveCards::ICardElement>> m_items;

};
}