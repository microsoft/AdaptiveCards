#pragma once

#include "pch.h"
#include "Enums.h"
#include "BaseCardElement.h"

namespace AdaptiveCards
{
class BaseCardElement;
class Container : public BaseCardElement, public std::enable_shared_from_this<Container>
{
public:
    Container();
    virtual std::string Serialize();
    const std::vector<std::shared_ptr<BaseCardElement>>& GetItems();

    void AddItem(std::shared_ptr<BaseCardElement>& item);
    std::shared_ptr<BaseCardElement> GetItem(const size_t index) const;

    static std::shared_ptr<Container> Deserialize(const Json::Value& root);

private:
    std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>> m_items;

};
}