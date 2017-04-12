#include "ColumnSet.h"
#include "ParseUtil.h"
#include "Image.h"
#include "TextBlock.h"

using namespace AdaptiveCards;

const std::unordered_map<CardElementType, std::function<std::shared_ptr<Column>(const Json::Value&)>, EnumHash> ColumnSet::ColumnParser =
{
    { CardElementType::Column, Column::Deserialize }
};

ColumnSet::ColumnSet() : BaseCardElement(CardElementType::ColumnSet)
{
}

ColumnSet::ColumnSet(std::vector<std::shared_ptr<Column>>& columns) : BaseCardElement(CardElementType::ColumnSet), m_columns(columns)
{
}

const std::vector<std::shared_ptr<Column>>& ColumnSet::GetColumns() const
{
    return m_columns;
}

std::vector<std::shared_ptr<Column>>& ColumnSet::GetColumns()
{
    return m_columns;
}

std::string ColumnSet::Serialize()
{
    return "";
}

std::shared_ptr<ColumnSet> ColumnSet::Deserialize(const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::ColumnSet);

    auto container = BaseCardElement::Deserialize<ColumnSet>(value);

    // Parse Columns
    auto cardElements = ParseUtil::GetElementCollection<Column>(value, AdaptiveCardSchemaKey::Columns, ColumnParser);
    container->m_columns = std::move(cardElements);
    return container;
}