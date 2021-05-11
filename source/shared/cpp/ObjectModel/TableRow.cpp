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
        m_verticalCellContentAlignment(VerticalAlignment::Top), m_cells({}), m_rtl({})
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

    VerticalAlignment TableRow::GetVerticalCellContentAlignment() const { return m_verticalCellContentAlignment; }
    void TableRow::SetVerticalCellContentAlignment(VerticalAlignment value) { m_verticalCellContentAlignment = value; }

    HorizontalAlignment TableRow::GetHorizontalCellContentAlignment() const { return m_horizontalCellContentAlignment; }
    void TableRow::SetHorizontalCellContentAlignment(HorizontalAlignment value)
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

        if (m_style != ContainerStyle::None)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ContainerStyleToString(m_style);
        }

        return root;
    }

    std::shared_ptr<BaseCardElement> TableRowParser::Deserialize(ParseContext& context, const Json::Value& json)
    {
        ParseUtil::ExpectTypeString(json, CardElementType::TableRow);

        std::shared_ptr<TableRow> tableRow = BaseCardElement::Deserialize<TableRow>(context, json);

        tableRow->SetHorizontalCellContentAlignment(ParseUtil::GetEnumValue<HorizontalAlignment>(
            json, AdaptiveCardSchemaKey::HorizontalCellContentAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString));
        tableRow->SetVerticalCellContentAlignment(ParseUtil::GetEnumValue<VerticalAlignment>(
            json, AdaptiveCardSchemaKey::VerticalCellContentAlignment, VerticalAlignment::Top, VerticalAlignmentFromString));
        tableRow->SetStyle(ParseUtil::GetEnumValue<ContainerStyle>(json, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString));
        auto cells = ParseUtil::GetElementCollection<TableCell>(
            false, context, json, AdaptiveCardSchemaKey::Cells, false, CardElementTypeToString(CardElementType::TableCell));
        tableRow->SetCells(cells);

        return tableRow;
    }

    std::shared_ptr<BaseCardElement> TableRowParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
    {
        return TableRowParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
    }
}
