// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTableCell.h"

#include <windows.foundation.collections.h>
#include <windows.ui.xaml.h>
#include <winrt/Windows.Foundation.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    AdaptiveTableCell::AdaptiveTableCell(const std::shared_ptr<::AdaptiveCards::TableCell>& sharedTableCell)
    {
        Items = GenerateContainedElementsProjection(sharedTableCell->GetItems());
        SelectAction = GenerateActionProjection(sharedTableCell->GetSelectAction());
        Style = static_cast<WinUI3::ContainerStyle>(sharedTableCell->GetStyle());
        if (sharedTableCell->GetVerticalContentAlignment())
        {
            VerticalContentAlignment = static_cast<WinUI3::VerticalContentAlignment>(*sharedTableCell->GetVerticalContentAlignment());
        }
        MinHeight = sharedTableCell->GetMinHeight();
        Bleed = sharedTableCell->GetBleed();
        BleedDirection = static_cast<WinUI3::BleedDirection>(sharedTableCell->GetBleedDirection());
        Rtl = sharedTableCell->GetRtl();

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
