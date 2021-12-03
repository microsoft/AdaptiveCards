// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveContainer.h"
#include "AdaptiveContainer.g.cpp"

#include <windows.foundation.collections.h>
#include <winrt/Windows.Foundation.h>

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveContainer::AdaptiveContainer(const std::shared_ptr<::AdaptiveCards::Container>& sharedContainer)
    {
        VerticalContentAlignment = opt_cast<Uwp::VerticalContentAlignment>(sharedContainer->GetVerticalContentAlignment());
        Items = GenerateContainedElementsProjection(sharedContainer->GetItems());
        SelectAction = GenerateActionProjection(sharedContainer->GetSelectAction());
        Style = static_cast<Uwp::ContainerStyle>(sharedContainer->GetStyle());
        MinHeight = sharedContainer->GetMinHeight();
        Bleed = sharedContainer->GetBleed();
        BleedDirection = static_cast<Uwp::BleedDirection>(sharedContainer->GetBleedDirection());
        Rtl = sharedContainer->GetRtl();

        auto backgroundImage = sharedContainer->GetBackgroundImage();
        if (backgroundImage && !backgroundImage->GetUrl().empty())
        {
            BackgroundImage = winrt::make<implementation::AdaptiveBackgroundImage>(backgroundImage);
        }

        InitializeBaseElement(sharedContainer);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveContainer::GetSharedModel()
    {
        auto container = std::make_shared<::AdaptiveCards::Container>();
        CopySharedElementProperties(*container);

        if (SelectAction.get())
        {
            container->SetSelectAction(GenerateSharedAction(SelectAction.get()));
        }

        if (VerticalContentAlignment)
        {
            container->SetVerticalContentAlignment(VerticalContentAlignment.get<::AdaptiveCards::VerticalContentAlignment>());
        }

        container->SetStyle(static_cast<::AdaptiveCards::ContainerStyle>(Style.get()));
        container->SetMinHeight(MinHeight);

        if (auto adaptiveBackgroundImage = peek_innards<implementation::AdaptiveBackgroundImage>(BackgroundImage.get()))
        {
            if (auto sharedBackgroundImage = adaptiveBackgroundImage->GetSharedModel())
            {
                container->SetBackgroundImage(sharedBackgroundImage);
            }
        }

        container->SetBleed(Bleed);
        container->SetRtl(Rtl);
        container->GetItems() = GenerateSharedElements(Items.get());

        return container;
    }
}
