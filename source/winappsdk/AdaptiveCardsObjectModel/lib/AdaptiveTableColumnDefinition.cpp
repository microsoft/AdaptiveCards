// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTableColumnDefinition.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    AdaptiveTableColumnDefinition::AdaptiveTableColumnDefinition(std::shared_ptr<::AdaptiveCards::TableColumnDefinition> const& sharedTableColumnDefinition)
    {
        if (sharedTableColumnDefinition->GetVerticalCellContentAlignment())
        {
            VerticalCellContentAlignment =
                static_cast<WinUI3::VerticalContentAlignment>(*sharedTableColumnDefinition->GetVerticalCellContentAlignment());
        }

        if (sharedTableColumnDefinition->GetHorizontalCellContentAlignment())
        {
            HorizontalCellContentAlignment =
                static_cast<WinUI3::HAlignment>(*sharedTableColumnDefinition->GetHorizontalCellContentAlignment());
        }

        Width = sharedTableColumnDefinition->GetWidth();
        PixelWidth = sharedTableColumnDefinition->GetPixelWidth();
    }

    std::shared_ptr<::AdaptiveCards::TableColumnDefinition> AdaptiveTableColumnDefinition::GetSharedModel()
    {
        auto tableColumnDefinition = std::make_shared<::AdaptiveCards::TableColumnDefinition>();

        if (VerticalCellContentAlignment)
        {
            tableColumnDefinition->SetVerticalCellContentAlignment(VerticalCellContentAlignment.get<::AdaptiveCards::VerticalContentAlignment>());
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
