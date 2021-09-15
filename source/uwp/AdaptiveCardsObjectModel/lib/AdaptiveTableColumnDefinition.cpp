// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTableColumnDefinition.h"
#include "AdaptiveTableColumnDefinition.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveTableColumnDefinition::AdaptiveTableColumnDefinition(std::shared_ptr<::AdaptiveCards::TableColumnDefinition> const& sharedTableColumnDefinition)
    {
        VerticalCellContentAlignment =
            opt_cast<Uwp::VerticalContentAlignment>(sharedTableColumnDefinition->GetVerticalCellContentAlignment());
        HorizontalCellContentAlignment =
            opt_cast<Uwp::HAlignment>(sharedTableColumnDefinition->GetHorizontalCellContentAlignment());
        Width = sharedTableColumnDefinition->GetWidth();
        PixelWidth = sharedTableColumnDefinition->GetPixelWidth();
    }

    std::shared_ptr<::AdaptiveCards::TableColumnDefinition> AdaptiveTableColumnDefinition::GetSharedModel()
    {
        auto tableColumnDefinition = std::make_shared<::AdaptiveCards::TableColumnDefinition>();

        if (VerticalCellContentAlignment)
        {
            tableColumnDefinition->SetVerticalCellContentAlignment(
                VerticalCellContentAlignment.get<::AdaptiveCards::VerticalContentAlignment>());
        }

        if (HorizontalCellContentAlignment)
        {
            tableColumnDefinition->SetHorizontalCellContentAlignment(
                HorizontalCellContentAlignment.get<::AdaptiveCards::HorizontalAlignment>());
        }

        tableColumnDefinition->SetWidth(Width);
        tableColumnDefinition->SetPixelWidth(PixelWidth);

        return tableColumnDefinition;
    }
}
