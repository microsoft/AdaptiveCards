// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveBackgroundImage.h"
#include "Column.h"
#include "AdaptiveColumn.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("d674610a-a76b-4283-bd09-b5a25c41433d") AdaptiveColumn : AdaptiveColumnT < AdaptiveColumn, ITypePeek>,AdaptiveCardElementBase
    {
        AdaptiveColumn(std::shared_ptr<::AdaptiveCards::Column> const& sharedColumn = std::make_shared<::AdaptiveCards::Column>());

        property<uint32_t> PixelWidth;

        hstring Width() { return m_width; }
        void Width(hstring const& width);
        hstring m_width;

        property<winrt::Windows::Foundation::Collections::IVector<Uwp::IAdaptiveCardElement>> Items;
        property_opt<Uwp::VerticalContentAlignment> VerticalContentAlignment;
        property<Uwp::AdaptiveBackgroundImage> BackgroundImage{nullptr};
        property_opt<bool> Rtl;
        property<Uwp::ContainerStyle> Style;
        property<Uwp::IAdaptiveActionElement> SelectAction;
        property<bool> Bleed;
        property<uint32_t> MinHeight;
        property<Uwp::BleedDirection> BleedDirection;

        auto ElementType() { return ElementType::Column; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveColumn : AdaptiveColumnT<AdaptiveColumn, implementation::AdaptiveColumn>
    {
    };
}
