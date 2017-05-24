#include "Column.h"
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

const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, EnumHash> Column::CardElementParsers =
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
    m_size = value;
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
    return "";
}

std::shared_ptr<Column> Column::Deserialize(const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::Column);

    auto column = BaseCardElement::Deserialize<Column>(value);

    column->SetSize(ParseUtil::GetValueAsString(value, AdaptiveCardSchemaKey::Size));

    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection<BaseCardElement>(value, AdaptiveCardSchemaKey::Items, CardElementParsers, true);
    column->m_items = std::move(cardElements);

    return column;
}

std::shared_ptr<Column> Column::DeserializeFromString(const std::string& jsonString)
{
    Json::Value jsonValue(jsonString);

    return Column::Deserialize(jsonValue);
}