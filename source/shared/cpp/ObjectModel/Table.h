// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include "CollectionCoreElement.h"
#include "TableColumnDefinition.h"
#include "TableRow.h"

namespace AdaptiveCards
{
    class Table : public CollectionCoreElement
    {
    public:
        Table();
        Table(const Table&) = default;
        Table(Table&&) = default;
        Table& operator=(const Table&) = default;
        Table& operator=(Table&&) = default;
        virtual ~Table() = default;

        Json::Value SerializeToJsonValue() const override;
        void DeserializeChildren(ParseContext& context, const Json::Value& value) override;

        bool GetShowGridLines() const;
        void SetShowGridLines(bool value);

        bool GetFirstRowAsHeaders() const;
        void SetFirstRowAsHeaders(bool value);

        std::optional<HorizontalAlignment> GetHorizontalCellContentAlignment() const;
        void SetHorizontalCellContentAlignment(std::optional<HorizontalAlignment> value);

        std::optional<VerticalContentAlignment> GetVerticalCellContentAlignment() const;
        void SetVerticalCellContentAlignment(std::optional<VerticalContentAlignment> value);

        ContainerStyle GetGridStyle() const;
        void SetGridStyle(ContainerStyle value);

        std::vector<std::shared_ptr<AdaptiveCards::TableColumnDefinition>>& GetColumns();
        const std::vector<std::shared_ptr<AdaptiveCards::TableColumnDefinition>>& GetColumns() const;
        void SetColumns(const std::vector<std::shared_ptr<AdaptiveCards::TableColumnDefinition>>& value);

        std::vector<std::shared_ptr<AdaptiveCards::TableRow>>& GetRows();
        const std::vector<std::shared_ptr<AdaptiveCards::TableRow>>& GetRows() const;
        void SetRows(const std::vector<std::shared_ptr<AdaptiveCards::TableRow>>& value);

    private:
        void PopulateKnownPropertiesSet();

        std::vector<std::shared_ptr<AdaptiveCards::TableColumnDefinition>> m_columnDefinitions;
        std::vector<std::shared_ptr<AdaptiveCards::TableRow>> m_rows;

        std::optional<HorizontalAlignment> m_horizontalCellContentAlignment;
        std::optional<VerticalContentAlignment> m_verticalCellContentAlignment;
        ContainerStyle m_gridStyle;

        bool m_showGridLines;
        bool m_firstRowAsHeaders;
    };

    class TableParser : public BaseCardElementParser
    {
    public:
        TableParser() = default;
        TableParser(const TableParser&) = default;
        TableParser(TableParser&&) = default;
        TableParser& operator=(const TableParser&) = default;
        TableParser& operator=(TableParser&&) = default;
        virtual ~TableParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
