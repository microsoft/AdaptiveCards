#include "ChoiceSetInput.h"
#include "ColumnSet.h"
#include "Container.h"
#include "FactSet.h"
#include "Image.h"
#include "ImageSet.h"
#include "DateInput.h"
#include "NumberInput.h"
#include "ParseUtil.h"
#include "TextBlock.h"
#include "TextInput.h"
#include "TimeInput.h"
#include "ToggleInput.h"

using namespace AdaptiveCards;

const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, EnumHash> Container::CardElementParsers =
{
    { CardElementType::ChoiceSetInput, ChoiceSetInput::Deserialize },
    { CardElementType::Container, Container::Deserialize },
    { CardElementType::ColumnSet, ColumnSet::Deserialize },
    { CardElementType::FactSet, FactSet::Deserialize },
    { CardElementType::Image, Image::Deserialize },
    { CardElementType::ImageSet, ImageSet::Deserialize },
    { CardElementType::TextBlock, TextBlock::Deserialize },
    { CardElementType::DateInput, DateInput::Deserialize },
    { CardElementType::NumberInput, NumberInput::Deserialize },
    { CardElementType::TextInput, TextInput::Deserialize },
    { CardElementType::TimeInput, TimeInput::Deserialize },
    { CardElementType::ToggleInput, ToggleInput::Deserialize },
};

Container::Container() : BaseCardElement(CardElementType::Container), m_style(ContainerStyle::None)
{
}

Container::Container(
    Spacing spacing,
    bool separator,
    ContainerStyle style,
    std::vector<std::shared_ptr<BaseCardElement>>& items) :
    BaseCardElement(CardElementType::Container, spacing, separator),
    m_style(style),
    m_items(items)
{
}

Container::Container(
    Spacing spacing,
    bool separator,
    ContainerStyle style) :
    BaseCardElement(CardElementType::Container, spacing, separator),
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

ContainerStyle Container::GetStyle() const
{
    return m_style;
}

void Container::SetStyle(const ContainerStyle value)
{
    m_style = value;
}

std::shared_ptr<BaseActionElement> Container::GetSelectAction() const
{
    return m_selectAction;
}

void Container::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}

std::string Container::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value Container::SerializeToJsonValue()
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ContainerStyleToString(GetStyle());

    std::string itemsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items);
    root[itemsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : GetItems())
    {
        root[itemsPropertyName].append(cardElement->SerializeToJsonValue());
    }

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] = BaseCardElement::SerializeSelectAction(GetSelectAction());

    return root;
}

std::shared_ptr<Container> Container::Deserialize(const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::Container);

    auto container = BaseCardElement::Deserialize<Container>(value);

    container->SetStyle(
        ParseUtil::GetEnumValue<ContainerStyle>(value, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString));

    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection<BaseCardElement>(value, AdaptiveCardSchemaKey::Items, Container::CardElementParsers, true);
    container->m_items = std::move(cardElements);

    container->SetSelectAction(BaseCardElement::DeserializeSelectAction(value, AdaptiveCardSchemaKey::SelectAction));

    return container;
}

std::shared_ptr<Container> Container::DeserializeFromString(const std::string& jsonString)
{
    return Container::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}