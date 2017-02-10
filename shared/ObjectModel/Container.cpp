#include "Container.h"
#include "ParseUtil.h"
#include "TextBlock.h"

using namespace AdaptiveCards;

Container::Container() : BaseCardElement(CardElementType::Container) {}

const std::vector<std::shared_ptr<BaseCardElement>>& AdaptiveCards::Container::GetItems()
{
    return m_items;
}
std::shared_ptr<BaseCardElement> Container::GetItem(size_t index) const
{
    if (m_items.size() <= index)
    {
        throw std::invalid_argument("Invalid Index");
    }
    return m_items[index];
}

void Container::AddItem(std::shared_ptr<BaseCardElement>& item)
{
    item->SetContainer(shared_from_this());
    m_items.emplace_back(item);
}

std::string Container::Serialize()
{
    return "";
}

std::shared_ptr<Container> Container::Deserialize(const Json::Value& root)
{
    // Try to get the cardelement container. If it it doesn't exist we return an empty container
    auto elementArray = root.get(CardElementTypeToString(CardElementType::Container), Json::Value());

    auto container = std::make_shared<Container>();
    if (elementArray.empty())
    {
        return container;
    }

    if (!elementArray.isArray())
    {
        throw AdaptiveCardParseException("Could not parse AdaptiveCard body. It was not an array");
    }

    // Map card type to the proper parser
    std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, EnumHash> cardElementParsers =
    {
        //{ CardElementType::ActionGroupType, ActionGroup::ParseJsonObject },
        //{ CardElementType::AdaptiveCardType, AdaptiveCard::ParseJsonObject },
        //{ CardElementType::ColumnGroupType, ColumnGroup::ParseJsonObject },
        //{ CardElementType::FactGroupType, FactGroup::ParseJsonObject },
        //{ CardElementType::ImageGalleryType, ImageGallery::ParseJsonObject },
        //{ CardElementType::ImageType, Image::ParseJsonObject },
        { CardElementType::TextBlock, TextBlock::Deserialize},
    };

    // Make sure the container fits the elements in the json file
    std::vector<std::shared_ptr<BaseCardElement>> elements(elementArray.size());
    std::transform(elementArray.begin(), elementArray.end(), elements.begin(), [&cardElementParsers](const Json::Value& cur)
    {
        // Get the element's type
        CardElementType curElementType = ParseUtil::TryGetCardElementType(cur);

        if (curElementType != CardElementType::Unsupported)
        {
            // Use the parser that maps to the type
            std::shared_ptr<BaseCardElement> cardElement = cardElementParsers[curElementType](cur);
            return cardElement;
        }
        return std::shared_ptr<BaseCardElement>();
    });

    for (std::shared_ptr<BaseCardElement> element : elements)
    {
        if (element != nullptr)
        {
            container->AddItem(element);
        }
    }
    return container;
}

