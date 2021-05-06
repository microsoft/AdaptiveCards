// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "TableColumnDefinition.h"
#include "TableRow.h"

namespace AdaptiveSharedNamespace
{
    class Table : public BaseCardElement
    {
    public:
        Table();
        Table(const Table&) = default;
        Table(Table&&) = default;
        Table& operator=(const Table&) = default;
        Table& operator=(Table&&) = default;
        virtual ~Table() = default;

        Json::Value SerializeToJsonValue() const override;

        bool GetShowGridLines() const;
        void SetShowGridLines(bool value);

        bool GetFirstRowAsHeaders() const;
        void SetFirstRowAsHeaders(bool value);

        HorizontalAlignment GetHorizontalCellContentAlignment() const;
        void SetHorizontalCellContentAlignment(HorizontalAlignment value);

        VerticalAlignment GetVerticalCellContentAlignment() const;
        void SetVerticalCellContentAlignment(VerticalAlignment value);

        ContainerStyle GetGridStyle() const;
        void SetGridStyle(ContainerStyle value);

        std::vector<std::shared_ptr<AdaptiveSharedNamespace::TableColumnDefinition>>& GetColumns();
        const std::vector<std::shared_ptr<AdaptiveSharedNamespace::TableColumnDefinition>>& GetColumns() const;
        void SetColumns(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::TableColumnDefinition>>& value);

        std::vector<std::shared_ptr<AdaptiveSharedNamespace::TableRow>>& GetRows();
        const std::vector<std::shared_ptr<AdaptiveSharedNamespace::TableRow>>& GetRows() const;
        void SetRows(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::TableRow>>& value);

    private:
        void PopulateKnownPropertiesSet();

        std::vector<std::shared_ptr<AdaptiveSharedNamespace::TableColumnDefinition>> m_columnDefinitions;
        std::vector<std::shared_ptr<AdaptiveSharedNamespace::TableRow>> m_rows;

        HorizontalAlignment m_horizontalCellContentAlignment;
        VerticalAlignment m_verticalCellContentAlignment;
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
