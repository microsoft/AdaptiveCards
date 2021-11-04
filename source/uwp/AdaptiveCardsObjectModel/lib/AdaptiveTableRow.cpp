// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTableRow.h"
#include "AdaptiveTableRow.g.cpp"
#include "AdaptiveTableCell.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveTableRow::AdaptiveTableRow(const std::shared_ptr<::AdaptiveCards::TableRow>& sharedTableRow)
    {
        VerticalCellContentAlignment =
            opt_cast<Uwp::VerticalContentAlignment>(sharedTableRow->GetVerticalCellContentAlignment());
        HorizontalCellContentAlignment = opt_cast<Uwp::HAlignment>(sharedTableRow->GetHorizontalCellContentAlignment());
        Style = static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::ContainerStyle>(sharedTableRow->GetStyle());
        Cells = GenerateVectorProjection<implementation::AdaptiveTableCell>(sharedTableRow->GetCells());
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveTableRow::GetSharedModel()
    {
        auto tableRow = std::make_shared<::AdaptiveCards::TableRow>();

        if (VerticalCellContentAlignment)
        {
            tableRow->SetVerticalCellContentAlignment(VerticalCellContentAlignment.get<::AdaptiveCards::VerticalContentAlignment>());
        }

        if (HorizontalCellContentAlignment)
        {
            tableRow->SetHorizontalCellContentAlignment(HorizontalCellContentAlignment.get<::AdaptiveCards::HorizontalAlignment>());
        }

        tableRow->SetStyle(static_cast<::AdaptiveCards::ContainerStyle>(Style.get()));
        tableRow->GetCells() = GenerateSharedVector<implementation::AdaptiveTableCell, ::AdaptiveCards::TableCell>(Cells.get());

        return tableRow;
    }
}
