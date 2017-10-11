#include "ColumnSet.h"
#include "ParseUtil.h"
#include "Image.h"
#include "TextBlock.h"

using namespace AdaptiveCards;

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

std::shared_ptr<BaseActionElement> ColumnSet::GetSelectAction() const
{
    return m_selectAction;
}

void ColumnSet::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}

std::string ColumnSet::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value ColumnSet::SerializeToJsonValue()
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    std::string propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Columns);
    root[propertyName] = Json::Value(Json::arrayValue);
    for (const auto& column : GetColumns())
    {
        root[propertyName].append(column->SerializeToJsonValue());
    }

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] = BaseCardElement::SerializeSelectAction(GetSelectAction());

    return root;
}

std::shared_ptr<ColumnSet> ColumnSet::Deserialize(const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::ColumnSet);

    auto container = BaseCardElement::Deserialize<ColumnSet>(value);

    // Parse Columns
    auto cardElements = ParseUtil::GetElementCollectionOfSingleType<Column>(value, AdaptiveCardSchemaKey::Columns, Column::Deserialize, true);
    container->m_columns = std::move(cardElements);

    container->SetSelectAction(BaseCardElement::DeserializeSelectAction(value, AdaptiveCardSchemaKey::SelectAction));

    return container;
}

std::shared_ptr<ColumnSet> ColumnSet::DeserializeFromString(const std::string& jsonString)
{
    return ColumnSet::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}