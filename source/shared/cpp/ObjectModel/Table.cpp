// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "Table.h"

namespace AdaptiveCards
{
    Table::Table() :
        BaseCardElement(CardElementType::Table), m_columnDefinitions({}), m_rows({}),
        m_horizontalCellContentAlignment(HorizontalAlignment::Left), m_verticalCellContentAlignment(VerticalAlignment::Top),
        m_gridStyle(ContainerStyle::None), m_showGridLines(false), m_firstRowAsHeaders(false)
    {
        PopulateKnownPropertiesSet();
    }

    void Table::PopulateKnownPropertiesSet()
    {
        m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Columns),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FirstRowAsHeaders),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::GridStyle),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalCellContentAlignment),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Rows),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ShowGridLines),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalCellContentAlignment)});
    }

    bool Table::GetShowGridLines() const { return m_showGridLines; }

    void Table::SetShowGridLines(bool value) { m_showGridLines = value; }

    bool Table::GetFirstRowAsHeaders() const { return m_firstRowAsHeaders; }

    void Table::SetFirstRowAsHeaders(bool value) { m_firstRowAsHeaders = value; }

    HorizontalAlignment Table::GetHorizontalCellContentAlignment() const { return m_horizontalCellContentAlignment; }

    void Table::SetHorizontalCellContentAlignment(HorizontalAlignment value)
    {
        m_horizontalCellContentAlignment = value;
    }

    VerticalAlignment Table::GetVerticalCellContentAlignment() const { return m_verticalCellContentAlignment; }

    void Table::SetVerticalCellContentAlignment(VerticalAlignment value) { m_verticalCellContentAlignment = value; }

    ContainerStyle Table::GetGridStyle() const { return m_gridStyle; }

    void Table::SetGridStyle(ContainerStyle value) { m_gridStyle = value; }

    std::vector<std::shared_ptr<TableColumnDefinition>>& Table::GetColumns() { return m_columnDefinitions; }
    const std::vector<std::shared_ptr<TableColumnDefinition>>& Table::GetColumns() const { return m_columnDefinitions; }

    void Table::SetColumns(const std::vector<std::shared_ptr<TableColumnDefinition>>& value)
    {
        m_columnDefinitions = value;
    }

    std::vector<std::shared_ptr<TableRow>>& Table::GetRows() { return m_rows; }
    const std::vector<std::shared_ptr<TableRow>>& Table::GetRows() const { return m_rows; }

    void Table::SetRows(const std::vector<std::shared_ptr<TableRow>>& value) { m_rows = value; }

    Json::Value Table::SerializeToJsonValue() const
    {
        Json::Value root = BaseCardElement::SerializeToJsonValue();

        if (!m_columnDefinitions.empty())
        {
            const std::string& columnsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Columns);
            root[columnsPropertyName] = Json::Value(Json::arrayValue);
            for (const auto& columnDefinition : m_columnDefinitions)
            {
                root[columnsPropertyName].append(columnDefinition->SerializeToJsonValue());
            }
        }

        if (!m_rows.empty())
        {
            const std::string& rowsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Rows);
            root[rowsPropertyName] = Json::Value(Json::arrayValue);
            for (const auto& row : m_rows)
            {
                root[rowsPropertyName].append(row->SerializeToJsonValue());
            }
        }

        if (m_showGridLines)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ShowGridLines)] = m_showGridLines;
        }

        if (m_firstRowAsHeaders)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FirstRowAsHeaders)] = m_firstRowAsHeaders;
        }

        if (m_gridStyle != ContainerStyle::None)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::GridStyle)] = ContainerStyleToString(m_gridStyle);
        }

        if (m_horizontalCellContentAlignment != HorizontalAlignment::Left)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalCellContentAlignment)] =
                HorizontalAlignmentToString(m_horizontalCellContentAlignment);
        }

        if (m_verticalCellContentAlignment != VerticalAlignment::Top)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalCellContentAlignment)] =
                VerticalAlignmentToString(m_verticalCellContentAlignment);
        }

        return root;
    }

    std::shared_ptr<BaseCardElement> TableParser::Deserialize(ParseContext& context, const Json::Value& json)
    {
        ParseUtil::ExpectTypeString(json, CardElementType::Table);

        std::shared_ptr<Table> table = BaseCardElement::Deserialize<Table>(context, json);
        table->SetShowGridLines(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::ShowGridLines, false, false));
        table->SetFirstRowAsHeaders(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::FirstRowAsHeaders, false, false));
        table->SetHorizontalCellContentAlignment(ParseUtil::GetEnumValue<HorizontalAlignment>(
            json, AdaptiveCardSchemaKey::HorizontalCellContentAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString));
        table->SetVerticalCellContentAlignment(ParseUtil::GetEnumValue<VerticalAlignment>(
            json, AdaptiveCardSchemaKey::VerticalCellContentAlignment, VerticalAlignment::Top, VerticalAlignmentFromString));

        // manually deserialize columns
        if (const auto& columnsArray = ParseUtil::GetArray(json, AdaptiveCardSchemaKey::Columns, false); !columnsArray.empty())
        {
            auto& columns = table->GetColumns();
            for (const auto& columnJson : columnsArray)
            {
                columns.push_back(TableColumnDefinition::Deserialize(context, columnJson));
            }
        }

        if (auto deserializedRows = ParseUtil::GetElementCollection<TableRow>(
                false, context, json, AdaptiveCardSchemaKey::Rows, false, CardElementTypeToString(CardElementType::TableRow));
            !deserializedRows.empty())
        {
            table->SetRows(deserializedRows);
        }

        return table;
    }

    std::shared_ptr<BaseCardElement> TableParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
    {
        return TableParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
    }
}
