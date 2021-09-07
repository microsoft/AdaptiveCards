// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTableColumnDefinition.h"
#include "AdaptiveTableColumnDefinition.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveTableColumnDefinition::AdaptiveTableColumnDefinition(std::shared_ptr<::AdaptiveCards::TableColumnDefinition> const& sharedTableColumnDefinition)
    {
        if (sharedTableColumnDefinition->GetVerticalCellContentAlignment().has_value())
        {
            VerticalCellContentAlignment =
                winrt::box_value(static_cast<Uwp::VerticalContentAlignment>(
                                     sharedTableColumnDefinition->GetVerticalCellContentAlignment().value()))
                    .as<Windows::Foundation::IReference<Uwp::VerticalContentAlignment>>();
        }

        if (sharedTableColumnDefinition->GetHorizontalCellContentAlignment().has_value())
        {
            HorizontalCellContentAlignment =
                winrt::box_value(
                    static_cast<Uwp::HAlignment>(sharedTableColumnDefinition->GetHorizontalCellContentAlignment().value()))
                    .as<Windows::Foundation::IReference<Uwp::HAlignment>>();
        }

        if (sharedTableColumnDefinition->GetWidth().has_value())
        {
            Width = winrt::box_value(sharedTableColumnDefinition->GetWidth().value()).as<Windows::Foundation::IReference<uint32_t>>();
        }

        if (sharedTableColumnDefinition->GetPixelWidth().has_value())
        {
            PixelWidth =
                winrt::box_value(sharedTableColumnDefinition->GetPixelWidth().value()).as<Windows::Foundation::IReference<uint32_t>>();
        }
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
