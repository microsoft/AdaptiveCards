#include "ColumnSet.h"
#include "Container.h"
#include "FactSet.h"
#include "Image.h"
#include "ImageSet.h"
#include "InputChoiceSet.h"
#include "InputDate.h"
#include "InputNumber.h"
#include "InputText.h"
#include "InputTime.h"
#include "InputToggle.h"
#include "ParseUtil.h"
#include "TextBlock.h"

using namespace AdaptiveCards;

const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, EnumHash> Container::CardElementParsers =
{
    { CardElementType::Container, Container::Deserialize },
    { CardElementType::ColumnSet, ColumnSet::Deserialize },
    { CardElementType::FactSet, FactSet::Deserialize },
    { CardElementType::Image, Image::Deserialize },
    { CardElementType::ImageSet, ImageSet::Deserialize },
    { CardElementType::TextBlock, TextBlock::Deserialize },
    { CardElementType::InputChoiceSet, InputChoiceSet::Deserialize },
    { CardElementType::InputDate, InputDate::Deserialize },
    { CardElementType::InputNumber, InputNumber::Deserialize },
    { CardElementType::InputText, InputText::Deserialize },
    { CardElementType::InputTime, InputTime::Deserialize },
    { CardElementType::InputToggle, InputToggle::Deserialize },
};

Container::Container() : BaseCardElement(CardElementType::Container), m_style(ContainerStyle::Normal)
{
}

Container::Container(
    SeparationStyle separation,
    std::string speak,
    ContainerStyle style,
    std::vector<std::shared_ptr<BaseCardElement>>& items) :
    BaseCardElement(CardElementType::Container, separation, speak),
    m_style(style),
    m_items(items)
{
}

Container::Container(
    SeparationStyle separation,
    std::string speak,
    ContainerStyle style) :
    BaseCardElement(CardElementType::Container, separation, speak),
    m_style(style)
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

ContainerStyle Container::GetContainerStyle() const
{
    return m_style;
}

void Container::SetContainerStyle(const ContainerStyle value)
{
    m_style = value;
}

std::string Container::Serialize()
{
    return "";
}

std::shared_ptr<Container> Container::Deserialize(const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::Container);

    auto container = BaseCardElement::Deserialize<Container>(value);

    container->SetContainerStyle(
        ParseUtil::GetEnumValue<ContainerStyle>(value, AdaptiveCardSchemaKey::Style, ContainerStyle::Normal, ContainerStyleFromString));

    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection<BaseCardElement>(value, AdaptiveCardSchemaKey::Items, Container::CardElementParsers);
    container->m_items = std::move(cardElements);
    return container;
}

std::shared_ptr<Container> Container::DeserializeFromString(const std::string& jsonString)
{
    Json::Value jsonValue(jsonString);

    return Container::Deserialize(jsonValue);
}