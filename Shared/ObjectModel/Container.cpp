#include "Container.h"

namespace AdaptiveCards
{
    std::vector<std::shared_ptr<ICardElement>>& AdaptiveCards::Container::GetItems()
    {
        return m_items;
    }
}

