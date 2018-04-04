#include "pch.h"
#include "ColumnSet.h"
#include "ParseUtil.h"
#include "Image.h"
#include "TextBlock.h"

using namespace AdaptiveSharedNamespace;

ColumnSet::ColumnSet() : BaseCardElement(CardElementType::ColumnSet)
{
    PopulateKnownPropertiesSet();
}

ColumnSet::ColumnSet(std::vector<std::shared_ptr<Column>>& columns) : BaseCardElement(CardElementType::ColumnSet), m_columns(columns)
{
    PopulateKnownPropertiesSet();
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

void ColumnSet::SetLanguage(const std::string& language)
{
    for (auto& column : m_columns)
    {
        column->SetLanguage(language);
    }
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

    std::shared_ptr<BaseActionElement> selectAction = GetSelectAction();
    if (selectAction != nullptr)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] = BaseCardElement::SerializeSelectAction(GetSelectAction());
    }

    return root;
}

std::shared_ptr<BaseCardElement> ColumnSetParser::Deserialize(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::ColumnSet);

    auto container = BaseCardElement::Deserialize<ColumnSet>(value);

    // Parse Columns
    auto cardElements = ParseUtil::GetElementCollectionOfSingleType<Column>(elementParserRegistration, actionParserRegistration, value, AdaptiveCardSchemaKey::Columns, Column::Deserialize, true);
    container->m_columns = std::move(cardElements);

    container->SetSelectAction(BaseCardElement::DeserializeSelectAction(elementParserRegistration, actionParserRegistration, value, AdaptiveCardSchemaKey::SelectAction));

    return container;
}

std::shared_ptr<BaseCardElement> ColumnSetParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return ColumnSetParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}

void ColumnSet::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Columns));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction));
}
