// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Container.h"
#include "AdaptiveBackgroundImage.h"
#include "AdaptiveContainer.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("d6031009-7039-4735-bd07-ab6d99b29f03") AdaptiveContainer : AdaptiveContainerT<AdaptiveContainer, ITypePeek>, AdaptiveCardElementBase
    {
        AdaptiveContainer(const std::shared_ptr<::AdaptiveCards::Container>& sharedcontainer = std::make_shared<::AdaptiveCards::Container>());

        // IAdaptiveCardElement
        auto ElementType() { return ElementType::Container; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        property<winrt::Windows::Foundation::Collections::IVector<Uwp::IAdaptiveCardElement>> Items;
        property<Uwp::IAdaptiveActionElement> SelectAction;
        property<Uwp::ContainerStyle> Style;
        property_opt<Uwp::VerticalContentAlignment> VerticalContentAlignment;
        property<Uwp::AdaptiveBackgroundImage> BackgroundImage{nullptr};
        property<uint32_t> MinHeight;
        property<bool> Bleed;
        property<Uwp::BleedDirection> BleedDirection;
        property_opt<bool> Rtl;
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveContainer : AdaptiveContainerT<AdaptiveContainer, implementation::AdaptiveContainer>
    {
    };
}
