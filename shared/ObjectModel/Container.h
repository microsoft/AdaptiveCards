#pragma once

#include <vector>
#include <memory>
#include "Enums.h"
#include "ICardElement.h"

namespace AdaptiveCards
{
class ICardElement;
class Container : public std::enable_shared_from_this<Container>, ICardElement
{
public:

    virtual std::string Serialize();
    const std::vector<std::shared_ptr<ICardElement>>& GetItems();

    void AddItem(std::shared_ptr<ICardElement>& item);
    std::shared_ptr<ICardElement> GetItem(const size_t index) const;

    static std::shared_ptr<Container> Deserialize(const Json::Value& root);

private:
    std::vector<std::shared_ptr<AdaptiveCards::ICardElement>> m_items;

};
}