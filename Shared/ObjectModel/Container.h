#pragma once

#include <vector>
#include <memory>
#include "enums.h"

namespace AdaptiveCards
{
    class ICardElement;

    class Container
    {
    public:
        ~Container() {};
        std::vector<std::shared_ptr<ICardElement>>& GetItems();

    private:
        std::vector<std::shared_ptr<AdaptiveCards::ICardElement>> m_items;
        TextColor m_textColor;
    };
}