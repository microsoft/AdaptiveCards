// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTableCell.h"
#include "AdaptiveTableCell.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveTableCell::AdaptiveTableCell(const std::shared_ptr<::AdaptiveCards::TableCell>& sharedTableCell)
    {
        Items = GenerateContainedElementsProjection(sharedTableCell->GetItems());
        SelectAction = GenerateActionProjection(sharedTableCell->GetSelectAction());
        Style = static_cast<Uwp::ContainerStyle>(sharedTableCell->GetStyle());
        if (sharedTableCell->GetVerticalContentAlignment().has_value())
        {
            VerticalContentAlignment = winrt::box_value(static_cast<Uwp::VerticalContentAlignment>(
                                                            sharedTableCell->GetVerticalContentAlignment().value()))
                                           .as<Windows::Foundation::IReference<Uwp::VerticalContentAlignment>>();
        }
        MinHeight = sharedTableCell->GetMinHeight();
        Bleed = sharedTableCell->GetBleed();
        BleedDirection = static_cast<Uwp::BleedDirection>(sharedTableCell->GetBleedDirection());
        if (sharedTableCell->GetRtl().has_value())
        {
            Rtl = winrt::box_value(sharedTableCell->GetRtl().value()).as<Windows::Foundation::IReference<bool>>();
        }

        auto backgroundImage = sharedTableCell->GetBackgroundImage();
        if (backgroundImage && !backgroundImage->GetUrl().empty())
        {
            BackgroundImage = winrt::make<implementation::AdaptiveBackgroundImage>(backgroundImage);
        }

        InitializeBaseElement(sharedTableCell);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveTableCell::GetSharedModel()
    {
        auto tableCell = std::make_shared<::AdaptiveCards::TableCell>();
        CopySharedElementProperties(*tableCell);

        if (SelectAction.get())
        {
            tableCell->SetSelectAction(GenerateSharedAction(SelectAction));
        }

        tableCell->SetStyle(static_cast<::AdaptiveCards::ContainerStyle>(Style.get()));

        if (VerticalContentAlignment.get())
        {
            tableCell->SetVerticalContentAlignment(VerticalContentAlignment.get<::AdaptiveCards::VerticalContentAlignment>());
        }

        tableCell->SetMinHeight(MinHeight);

        auto adaptiveBackgroundImage = peek_innards<implementation::AdaptiveBackgroundImage>(BackgroundImage.get());
        std::shared_ptr<::AdaptiveCards::BackgroundImage> sharedBackgroundImage;
        if (adaptiveBackgroundImage && (sharedBackgroundImage = adaptiveBackgroundImage->GetSharedModel()))
        {
            tableCell->SetBackgroundImage(sharedBackgroundImage);
        }

        tableCell->SetBleed(Bleed);
        tableCell->SetRtl(Rtl);
        tableCell->GetItems() = GenerateSharedElements(Items.get());

        return tableCell;
    }
}
