// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "TableRow.h"
#include "TableCell.h"
#include "ParseUtil.h"

namespace AdaptiveCards
{
    TableRow::TableRow() :
        BaseCardElement(CardElementType::TableRow), m_style(ContainerStyle::None),
        m_horizontalCellContentAlignment(HorizontalAlignment::Left),
        m_verticalCellContentAlignment(VerticalContentAlignment::Top), m_cells({}), m_rtl({})
    {
        PopulateKnownPropertiesSet();
    }

    void TableRow::PopulateKnownPropertiesSet()
    {
        m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Cells),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalCellContentAlignment),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Rtl),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalCellContentAlignment)});
    }

    std::vector<std::shared_ptr<TableCell>>& TableRow::GetCells() { return m_cells; }
    const std::vector<std::shared_ptr<TableCell>>& TableRow::GetCells() const { return m_cells; }
    void TableRow::SetCells(const std::vector<std::shared_ptr<TableCell>>& value) { m_cells = value; }

    std::optional<VerticalContentAlignment> TableRow::GetVerticalCellContentAlignment() const
    {
        return m_verticalCellContentAlignment;
    }
    void TableRow::SetVerticalCellContentAlignment(std::optional<VerticalContentAlignment> value)
    {
        m_verticalCellContentAlignment = value;
    }

    std::optional<HorizontalAlignment> TableRow::GetHorizontalCellContentAlignment() const
    {
        return m_horizontalCellContentAlignment;
    }
    void TableRow::SetHorizontalCellContentAlignment(std::optional<HorizontalAlignment> value)
    {
        m_horizontalCellContentAlignment = value;
    }

    ContainerStyle TableRow::GetStyle() const { return m_style; }
    void TableRow::SetStyle(const ContainerStyle value) { m_style = value; }

    Json::Value TableRow::SerializeToJsonValue() const
    {
        Json::Value root = BaseCardElement::SerializeToJsonValue();

        if (!m_cells.empty())
        {
            const std::string& cellsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Cells);
            root[cellsPropertyName] = Json::Value(Json::arrayValue);
            for (const auto& cardElement : m_cells)
            {
                root[cellsPropertyName].append(cardElement->SerializeToJsonValue());
            }
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

        if (m_style != ContainerStyle::None)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ContainerStyleToString(m_style);
        }

        return root;
    }

    std::shared_ptr<TableRow> TableRow::DeserializeTableRowFromString(ParseContext& context, const std::string& json)
    {
        return DeserializeTableRow(context, ParseUtil::GetJsonValueFromString(json));
    }

    std::shared_ptr<TableRow> TableRow::DeserializeTableRow(ParseContext& context, const Json::Value& json)
    {
        std::shared_ptr<TableRow> tableRow = BaseCardElement::Deserialize<TableRow>(context, json);

        tableRow->SetHorizontalCellContentAlignment(ParseUtil::GetOptionalEnumValue<HorizontalAlignment>(
            json, AdaptiveCardSchemaKey::HorizontalCellContentAlignment, HorizontalAlignmentFromString));
        tableRow->SetVerticalCellContentAlignment(ParseUtil::GetOptionalEnumValue<VerticalContentAlignment>(
            json, AdaptiveCardSchemaKey::VerticalCellContentAlignment, VerticalContentAlignmentFromString));
        tableRow->SetStyle(ParseUtil::GetEnumValue<ContainerStyle>(json, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString));
        auto cells = ParseUtil::GetElementCollectionOfSingleType<TableCell>(
            context, json, AdaptiveCardSchemaKey::Cells, &TableCell::DeserializeTableCell, false);
        tableRow->SetCells(cells);

        return tableRow;
    }
}
