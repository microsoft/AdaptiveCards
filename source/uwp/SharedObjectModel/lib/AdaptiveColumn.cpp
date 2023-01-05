// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveColumn.h"
#include "AdaptiveColumn.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveColumn::AdaptiveColumn(std::shared_ptr<::AdaptiveCards::Column> const& sharedColumn)
    {
        Items = GenerateContainedElementsProjection(sharedColumn->GetItems());
        SelectAction = GenerateActionProjection(sharedColumn->GetSelectAction());
        Style = static_cast<Uwp::ContainerStyle>(sharedColumn->GetStyle());
        VerticalContentAlignment = opt_cast<Uwp::VerticalContentAlignment>(sharedColumn->GetVerticalContentAlignment());
        Bleed = sharedColumn->GetBleed();
        BleedDirection = static_cast<Uwp::BleedDirection>(sharedColumn->GetBleedDirection());
        m_width = UTF8ToHString(sharedColumn->GetWidth());
        PixelWidth = sharedColumn->GetPixelWidth();
        MinHeight = sharedColumn->GetMinHeight();
        Rtl = sharedColumn->GetRtl();

        auto backgroundImage = sharedColumn->GetBackgroundImage();
        if (backgroundImage && !backgroundImage->GetUrl().empty())
        {
            BackgroundImage = winrt::make<implementation::AdaptiveBackgroundImage>(backgroundImage);
        }

        InitializeBaseElement(sharedColumn);
    }

    void AdaptiveColumn::Width(hstring const& width)
    {
        m_width = width;
        PixelWidth = ParseSizeForPixelSize(HStringToUTF8(width), nullptr).value_or(0);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveColumn::GetSharedModel()
    {
        auto column = std::make_shared<::AdaptiveCards::Column>();
        CopySharedElementProperties(*column);

        column->SetStyle(static_cast<::AdaptiveCards::ContainerStyle>(Style.get()));

        if (VerticalContentAlignment)
        {
            column->SetVerticalContentAlignment(VerticalContentAlignment.get<::AdaptiveCards::VerticalContentAlignment>());
        }

        if (PixelWidth)
        {
            column->SetPixelWidth(PixelWidth);
        }
        else
        {
            column->SetWidth(HStringToUTF8(m_width));
        }

        column->SetMinHeight(MinHeight);
        column->SetBleed(Bleed);

        if (auto adaptiveBackgroundImage = peek_innards<implementation::AdaptiveBackgroundImage>(BackgroundImage.get()))
        {
            if (auto sharedBackgroundImage = adaptiveBackgroundImage->GetSharedModel())
            {
                column->SetBackgroundImage(sharedBackgroundImage);
            }
        }

        if (SelectAction != nullptr)
        {
            column->SetSelectAction(GenerateSharedAction(SelectAction));
        }

        column->SetRtl(Rtl.get());

        column->GetItems() = GenerateSharedElements(Items.get());

        return column;
    }
}
