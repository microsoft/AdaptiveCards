// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveBackgroundImage.h"
#include "Column.h"
#include "AdaptiveColumn.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct DECLSPEC_UUID("d674610a-a76b-4283-bd09-b5a25c41433d") AdaptiveColumn : AdaptiveColumnT < AdaptiveColumn, ITypePeek>,AdaptiveCardElementBase
    {
        AdaptiveColumn(std::shared_ptr<::AdaptiveCards::Column> const& sharedColumn = std::make_shared<::AdaptiveCards::Column>());

        property<uint32_t> PixelWidth;

        hstring Width() { return m_width; }
        void Width(hstring const& width);
        hstring m_width;

        property<winrt::Windows::Foundation::Collections::IVector<Xaml_OM::IAdaptiveCardElement>> Items;
        property_opt<Xaml_OM::VerticalContentAlignment> VerticalContentAlignment;
        property<Xaml_OM::AdaptiveBackgroundImage> BackgroundImage{nullptr};
        property_opt<bool> Rtl;
        property<Xaml_OM::ContainerStyle> Style;
        property<Xaml_OM::IAdaptiveActionElement> SelectAction;
        property<bool> Bleed;
        property<uint32_t> MinHeight;
        property<Xaml_OM::BleedDirection> BleedDirection;

        auto ElementType() { return ElementType::Column; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveColumn : AdaptiveColumnT<AdaptiveColumn, implementation::AdaptiveColumn>
    {
    };
}
