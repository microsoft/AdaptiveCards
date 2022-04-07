// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "BaseCardElement.h"
#include "TableCell.h"

namespace AdaptiveCards
{
class BaseCardElement;

class TableRow : public BaseCardElement
{
public:
    TableRow();
    TableRow(const TableRow&) = default;
    TableRow(TableRow&&) = default;
    TableRow& operator=(const TableRow&) = default;
    TableRow& operator=(TableRow&&) = default;
    virtual ~TableRow() = default;

    Json::Value SerializeToJsonValue() const override;

    std::vector<std::shared_ptr<AdaptiveCards::TableCell>>& GetCells();
    const std::vector<std::shared_ptr<AdaptiveCards::TableCell>>& GetCells() const;
    void SetCells(const std::vector<std::shared_ptr<AdaptiveCards::TableCell>>& value);

    std::optional<VerticalContentAlignment> GetVerticalCellContentAlignment() const;
    void SetVerticalCellContentAlignment(std::optional<VerticalContentAlignment> value);

    std::optional<HorizontalAlignment> GetHorizontalCellContentAlignment() const;
    void SetHorizontalCellContentAlignment(std::optional<HorizontalAlignment> value);

    ContainerStyle GetStyle() const;
    void SetStyle(const ContainerStyle value);

    static std::shared_ptr<TableRow> DeserializeTableRowFromString(ParseContext& context, const std::string& root);
    static std::shared_ptr<TableRow> DeserializeTableRow(ParseContext& context, const Json::Value& root);

private:
    void PopulateKnownPropertiesSet();

    ContainerStyle m_style;

    std::optional<HorizontalAlignment> m_horizontalCellContentAlignment;
    std::optional<VerticalContentAlignment> m_verticalCellContentAlignment;

    std::vector<std::shared_ptr<AdaptiveCards::TableCell>> m_cells;
    std::optional<bool> m_rtl;
};
} // namespace AdaptiveCards
