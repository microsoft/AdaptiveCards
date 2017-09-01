#include "ChoiceSetInput.h"
#include "Column.h"
#include "ColumnSet.h"
#include "Container.h"
#include "DateInput.h"
#include "FactSet.h"
#include "Image.h"
#include "ImageSet.h"
#include "NumberInput.h"
#include "ParseUtil.h"
#include "TextBlock.h"
#include "TextInput.h"
#include "TimeInput.h"
#include "ToggleInput.h"

using namespace AdaptiveCards;

const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, EnumHash> Column::CardElementParsers =
{
    { CardElementType::Container, Container::Deserialize },
    { CardElementType::ColumnSet, ColumnSet::Deserialize },
    { CardElementType::FactSet, FactSet::Deserialize },
    { CardElementType::Image, Image::Deserialize },
    { CardElementType::ImageSet, ImageSet::Deserialize },
    { CardElementType::TextBlock, TextBlock::Deserialize },
    { CardElementType::ChoiceSetInput, ChoiceSetInput::Deserialize },
    { CardElementType::DateInput, DateInput::Deserialize },
    { CardElementType::NumberInput, NumberInput::Deserialize },
    { CardElementType::TextInput, TextInput::Deserialize },
    { CardElementType::TimeInput, TimeInput::Deserialize },
    { CardElementType::ToggleInput, ToggleInput::Deserialize },
};

Column::Column() : BaseCardElement(CardElementType::Column), m_size("Auto")
{
}

Column::Column(
    SeparationStyle separation,
    std::string speak,
    std::string size,
    std::vector<std::shared_ptr<BaseCardElement>>& items) :
    BaseCardElement(CardElementType::Column, separation, speak), m_size(size), m_items(items)
{
}

Column::Column(
    SeparationStyle separation,
    std::string speak,
    std::string size) :
    BaseCardElement(CardElementType::Column, separation, speak), m_size(size)
{
}

std::string Column::GetSize() const
{
    return m_size;
}

void Column::SetSize(const std::string value)
{
    m_size = ParseUtil::ToLowercase(value);
}

const std::vector<std::shared_ptr<BaseCardElement>>& Column::GetItems() const
{
    return m_items;
}

std::vector<std::shared_ptr<BaseCardElement>>& Column::GetItems()
{
    return m_items;
}

std::string Column::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value Column::SerializeToJsonValue()
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size)] = GetSize();

    std::string propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items);
    root[propertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : GetItems())
    {
        root[propertyName].append(cardElement->SerializeToJsonValue());
    }

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] = BaseCardElement::SerializeSelectAction(GetSelectAction());

    return root;
}

std::shared_ptr<Column> Column::Deserialize(const Json::Value& value)
{
    auto column = BaseCardElement::Deserialize<Column>(value);

    column->SetSize(ParseUtil::GetValueAsString(value, AdaptiveCardSchemaKey::Size));

    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection<BaseCardElement>(value, AdaptiveCardSchemaKey::Items, CardElementParsers, true);
    column->m_items = std::move(cardElements);

    column->SetSelectAction(BaseCardElement::DeserializeSelectAction(value, AdaptiveCardSchemaKey::SelectAction));

    return column;
}

std::shared_ptr<Column> Column::DeserializeFromString(const std::string& jsonString)
{
    return Column::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::shared_ptr<BaseActionElement> Column::GetSelectAction() const
{
    return m_selectAction;
}

void Column::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}