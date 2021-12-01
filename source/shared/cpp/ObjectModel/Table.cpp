// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "Table.h"

namespace AdaptiveCards
{
    Table::Table() :
        CollectionCoreElement(CardElementType::Table), m_columnDefinitions({}), m_rows({}),
        m_gridStyle(ContainerStyle::None), m_showGridLines(true), m_firstRowAsHeaders(true)
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

    std::optional<HorizontalAlignment> Table::GetHorizontalCellContentAlignment() const
    {
        return m_horizontalCellContentAlignment;
    }

    void Table::SetHorizontalCellContentAlignment(std::optional<HorizontalAlignment> value)
    {
        m_horizontalCellContentAlignment = value;
    }

    std::optional<VerticalContentAlignment> Table::GetVerticalCellContentAlignment() const
    {
        return m_verticalCellContentAlignment;
    }

    void Table::SetVerticalCellContentAlignment(std::optional<VerticalContentAlignment> value)
    {
        m_verticalCellContentAlignment = value;
    }

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

    void Table::DeserializeChildren(ParseContext& context, const Json::Value& value)
    {
        if (auto deserializedRows =
                ParseUtil::GetElementCollectionOfSingleType<TableRow>(
                    context, value, AdaptiveCardSchemaKey::Rows, &TableRow::DeserializeTableRow, false); !deserializedRows.empty())
        {
            m_rows = deserializedRows;
        }
    }

    Json::Value Table::SerializeToJsonValue() const
    {
        Json::Value root = CollectionCoreElement::SerializeToJsonValue();

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

        if (m_showGridLines != true)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ShowGridLines)] = m_showGridLines;
        }

        if (m_firstRowAsHeaders != true)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FirstRowAsHeaders)] = m_firstRowAsHeaders;
        }

        if (m_gridStyle != ContainerStyle::None)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::GridStyle)] = ContainerStyleToString(m_gridStyle);
        }

        if (m_horizontalCellContentAlignment.has_value())
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalCellContentAlignment)] =
                HorizontalAlignmentToString(m_horizontalCellContentAlignment.value_or(HorizontalAlignment::Left));
        }

        if (m_verticalCellContentAlignment.has_value())
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalCellContentAlignment)] =
                VerticalContentAlignmentToString(m_verticalCellContentAlignment.value_or(VerticalContentAlignment::Top));
        }

        return root;
    }

    std::shared_ptr<BaseCardElement> TableParser::Deserialize(ParseContext& context, const Json::Value& json)
    {
        ParseUtil::ExpectTypeString(json, CardElementType::Table);

        std::shared_ptr<Table> table = CollectionCoreElement::Deserialize<Table>(context, json);

        if (const auto& columnsArray = ParseUtil::GetArray(json, AdaptiveCardSchemaKey::Columns, false); !columnsArray.empty())
        {
            auto& columns = table->GetColumns();
            for (const auto& columnJson : columnsArray)
            {
                columns.push_back(TableColumnDefinition::Deserialize(context, columnJson));
            }
        }

        table->SetShowGridLines(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::ShowGridLines, true, false));
        table->SetGridStyle(
            ParseUtil::GetEnumValue<ContainerStyle>(json, AdaptiveCardSchemaKey::GridStyle, ContainerStyle::None, ContainerStyleFromString));
        table->SetFirstRowAsHeaders(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::FirstRowAsHeaders, true, false));
        table->SetHorizontalCellContentAlignment(ParseUtil::GetOptionalEnumValue<HorizontalAlignment>(
            json, AdaptiveCardSchemaKey::HorizontalCellContentAlignment, HorizontalAlignmentFromString));
        table->SetVerticalCellContentAlignment(ParseUtil::GetOptionalEnumValue<VerticalContentAlignment>(
            json, AdaptiveCardSchemaKey::VerticalCellContentAlignment, VerticalContentAlignmentFromString));

        return table;
    }

    std::shared_ptr<BaseCardElement> TableParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
    {
        return TableParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
    }
}
