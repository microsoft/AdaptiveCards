#include "Column.h"
#include "ParseUtil.h"
#include "Image.h"
#include "TextBlock.h"

using namespace AdaptiveCards;

Column::Column() : Container(), m_size("Auto")
{
}

Column::Column(
    SeparationStyle separation,
    std::string speak,
    std::string size,
    std::vector<std::shared_ptr<BaseCardElement>>& items) :
    Container(separation, speak, items), m_size(size)
{
}

Column::Column(
    SeparationStyle separation,
    std::string speak,
    std::string size) :
    Container(separation, speak), m_size(size)
{
}

const CardElementType Column::GetElementType() const
{
    return CardElementType::Column;
}

std::string Column::GetSize() const
{
    return m_size;
}

void Column::SetSize(const std::string value)
{
    m_size = value;
}


std::string Column::Serialize()
{
    return "";
}

std::shared_ptr<Column> Column::Deserialize(const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::Column);

    auto column = BaseCardElement::Deserialize<Column>(value);

    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection<BaseCardElement>(value, AdaptiveCardSchemaKey::Items, Container::CardElementParsers);
    column->SetItems(cardElements);
    return column;
}

std::shared_ptr<Column> Column::DeserializeFromString(const std::string& jsonString)
{
    Json::Value jsonValue(jsonString);

    return Column::Deserialize(jsonValue);
}