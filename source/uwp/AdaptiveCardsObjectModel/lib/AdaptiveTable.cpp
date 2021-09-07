// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTable.h"
#include "AdaptiveTable.g.cpp"
#include "AdaptiveTableRow.h"
#include "AdaptiveTableColumnDefinition.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveTable::AdaptiveTable(std::shared_ptr<::AdaptiveCards::Table> const& sharedTable)
    {
        ShowGridLines = sharedTable->GetShowGridLines();
        FirstRowAsHeaders = sharedTable->GetFirstRowAsHeaders();

        if (sharedTable->GetVerticalCellContentAlignment().has_value())
        {
            VerticalCellContentAlignment = winrt::box_value(static_cast<Uwp::VerticalContentAlignment>(
                                                                sharedTable->GetVerticalCellContentAlignment().value()))
                                               .as<Windows::Foundation::IReference<Uwp::VerticalContentAlignment>>();
        }

        if (sharedTable->GetHorizontalCellContentAlignment().has_value())
        {
            HorizontalCellContentAlignment =
                winrt::box_value(static_cast<Uwp::HAlignment>(sharedTable->GetHorizontalCellContentAlignment().value()))
                    .as<Windows::Foundation::IReference<Uwp::HAlignment>>();
        }

        GridStyle = static_cast<Uwp::ContainerStyle>(sharedTable->GetGridStyle());
        Rows = GenerateVectorProjection<implementation::AdaptiveTableRow>(sharedTable->GetRows());
        Columns = GenerateVectorProjection<implementation::AdaptiveTableColumnDefinition>(sharedTable->GetColumns());

        InitializeBaseElement(sharedTable);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveTable::GetSharedModel()
    {
        auto table = std::make_shared<::AdaptiveCards::Table>();
        CopySharedElementProperties(*table);

        table->SetShowGridLines(ShowGridLines);
        table->SetFirstRowAsHeaders(FirstRowAsHeaders);

        if (VerticalCellContentAlignment)
        {
            table->SetVerticalCellContentAlignment(VerticalCellContentAlignment.get<::AdaptiveCards::VerticalContentAlignment>());
        }

        if (HorizontalCellContentAlignment)
        {
            table->SetHorizontalCellContentAlignment(HorizontalCellContentAlignment.get<::AdaptiveCards::HorizontalAlignment>());
        }

        table->SetGridStyle(static_cast<::AdaptiveCards::ContainerStyle>(GridStyle.get()));
        table->GetRows() = GenerateSharedVector<implementation::AdaptiveTableRow, ::AdaptiveCards::TableRow>(Rows.get());
        table->GetColumns() =
            GenerateSharedVector<implementation::AdaptiveTableColumnDefinition, ::AdaptiveCards::TableColumnDefinition>(
                Columns.get());

        return table;
    }
}
