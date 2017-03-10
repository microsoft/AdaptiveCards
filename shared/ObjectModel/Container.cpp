#include "Container.h"
#include "ParseUtil.h"
#include "Image.h"
#include "TextBlock.h"

using namespace AdaptiveCards;

const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>> Container::CardElementParsers =
{
    //{ CardElementType::ActionGroupType, ActionGroup::ParseJsonObject },
    //{ CardElementType::AdaptiveCardType, AdaptiveCard::ParseJsonObject },
    //{ CardElementType::FactGroupType, FactGroup::ParseJsonObject },
    //{ CardElementType::ImageGalleryType, ImageGallery::ParseJsonObject },
    { CardElementType::Container, Container::Deserialize },
    { CardElementType::Image, Image::Deserialize },
    { CardElementType::TextBlock, TextBlock::Deserialize },
};

Container::Container() : BaseCardElement(CardElementType::Container)
{
}

Container::Container(
    SeparationStyle separation,
    std::string speak,
    std::vector<std::shared_ptr<BaseCardElement>>& items) :
    BaseCardElement(CardElementType::Container, separation, speak),
    m_items(items)
{
}

Container::Container(
    SeparationStyle separation,
    std::string speak) :
    BaseCardElement(CardElementType::Container, separation, speak)
{
}

const std::vector<std::shared_ptr<BaseCardElement>>& Container::GetItems() const
{
    return m_items;
}

std::vector<std::shared_ptr<BaseCardElement>>& Container::GetItems()
{
    return m_items;
}

std::string Container::Serialize()
{
    return "";
}

std::shared_ptr<Container> Container::Deserialize(const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::Container);

    auto container = BaseCardElement::Deserialize<Container>(value);

    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection<BaseCardElement>(value, AdaptiveCardSchemaKey::Items, Container::CardElementParsers);
    container->m_items = std::move(cardElements);
    return container;
}