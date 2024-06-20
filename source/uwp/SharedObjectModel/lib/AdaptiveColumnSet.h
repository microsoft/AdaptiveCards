// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ColumnSet.h"
#include "AdaptiveColumnSet.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct DECLSPEC_UUID("3f54eed2-03e8-480b-aede-6f4faae4b731") AdaptiveColumnSet : AdaptiveColumnSetT<AdaptiveColumnSet, ITypePeek>, AdaptiveCardElementBase
    {
        AdaptiveColumnSet(const std::shared_ptr<::AdaptiveCards::ColumnSet>& sharedColumnSet = std::make_unique<::AdaptiveCards::ColumnSet>());

        property<winrt::Windows::Foundation::Collections::IVector<Xaml_OM::AdaptiveColumn>> Columns;
        property<Xaml_OM::IAdaptiveActionElement> SelectAction;
        property<Xaml_OM::ContainerStyle> Style;
        property<uint32_t> MinHeight;
        property<bool> Bleed;
        property<Xaml_OM::BleedDirection> BleedDirection;
        property_opt<Xaml_OM::HAlignment> HorizontalAlignment;

        // IAdaptiveCardElement
        auto ElementType() { return Xaml_OM::ElementType::ColumnSet; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveColumnSet : AdaptiveColumnSetT<AdaptiveColumnSet, implementation::AdaptiveColumnSet>
    {
    };
}
