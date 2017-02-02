#include "Container.h"
#include "TextBlock.h"
#include <unordered_map>
#include <algorithm>

namespace AdaptiveCards
{
std::vector<std::shared_ptr<ICardElement>>& AdaptiveCards::Container::GetItems()
{
    return m_items;
}
int aoeu(const std::string& foo) {
    return 0;}

std::shared_ptr<Container> Container::Deserialize(const Json::Value& root)
{
    // Try to get the cardelement container. If it it doesn't exist we return an empty container
    auto elementArray = root.get(CardElementTypeToString(CardElementType::ContainerType), Json::Value());

    auto container = std::make_shared<Container>();
    if (elementArray.empty())
    {
        return container;
    }

    if (!elementArray.isArray())
    {
        throw ACParseException("Could not parse AdaptiveCard body. It was not an array");
    }

    // Map card type to the proper parser
    std::unordered_map<CardElementType, std::function<std::shared_ptr<ICardElement>(const Json::Value&)>> cardElementParsers =
    {
        //{ CardElementType::ActionGroupType, ActionGroup::ParseJsonObject },
        //{ CardElementType::AdaptiveCardType, AdaptiveCard::ParseJsonObject },
        //{ CardElementType::ColumnGroupType, ColumnGroup::ParseJsonObject },
        //{ CardElementType::FactGroupType, FactGroup::ParseJsonObject },
        //{ CardElementType::ImageGalleryType, ImageGallery::ParseJsonObject },
        //{ CardElementType::ImageType, Image::ParseJsonObject },
        { CardElementType::TextBlockType, TextBlock::Deserialize},
    };

    //container->GetItems().resize(elementArray.size()); // Make sure the container fits the elements in the json file
    std::vector<std::shared_ptr<ICardElement>> elements(elementArray.size());
    std::transform(elementArray.begin(), elementArray.end(), elements.begin(), [&cardElementParsers](const Json::Value& cur)
    {
        // Get the body type
        CardElementType curBodyType = ACParser::GetCardElementType(cur);

        // Use the parser that maps to the bodytype
        std::shared_ptr<ICardElement> cardElement = cardElementParsers[curBodyType](cur);
        return cardElement;
    });

    for (size_t i = 0; i < elements.size(); i++)
    {
        container->GetItems().emplace_back(elements[i]);
    }
    return container;
}
}

