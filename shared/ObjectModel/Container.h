#pragma once

#include "pch.h"
#include "Enums.h"
#include "BaseCardElement.h"

namespace AdaptiveCards
{
class BaseCardElement;
class Container : public std::enable_shared_from_this<Container>, BaseCardElement
{
public:
    Container();
    Container(std::shared_ptr<Container> parent,
        HorizontalAlignment horizontalAlignment,
        CardElementSize size,
        std::string speak,
        bool startGroup
    );

    Container(std::shared_ptr<Container> parent,
        HorizontalAlignment horizontalAlignment,
        CardElementSize size,
        std::string speak,
        bool startGroup,
        std::vector<std::shared_ptr<BaseCardElement>> &items
    );

    virtual std::string Serialize();
    const std::vector<std::shared_ptr<BaseCardElement>>& GetItems();

    bool GetStartGroup() const;
    void SetStartGroup(bool value);

    void AddItem(std::shared_ptr<BaseCardElement>& item);
    std::shared_ptr<BaseCardElement> GetItem(const size_t index) const;

    static std::shared_ptr<Container> Deserialize(const Json::Value& root);

private:
    bool m_startGroup;
    std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>> m_items;
};
}