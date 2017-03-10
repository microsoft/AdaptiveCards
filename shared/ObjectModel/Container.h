#pragma once

#include "pch.h"
#include "Enums.h"
#include "BaseCardElement.h"

namespace AdaptiveCards
{
class BaseCardElement;
class Container : public BaseCardElement
{
public:
    Container();
    Container(SeparationStyle separation, std::string speak);
    Container(SeparationStyle separation, std::string speak, std::vector<std::shared_ptr<BaseCardElement>>& items);

    virtual std::string Serialize();

    std::vector<std::shared_ptr<BaseCardElement>>& GetItems();
    const std::vector<std::shared_ptr<BaseCardElement>>& GetItems() const;
    static std::shared_ptr<Container> Deserialize(const Json::Value& root);

private:
    std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>> m_items;
};
}