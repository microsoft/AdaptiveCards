// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ActionSet.h"
#include "AdaptiveActionSet.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("d6031009-7039-4735-bd07-ab6d99b29f03") AdaptiveActionSet : AdaptiveActionSetT < AdaptiveActionSet, ITypePeek>,
        AdaptiveCardElementBase
    {
        AdaptiveActionSet() : AdaptiveActionSet(std::make_shared<::AdaptiveCards::ActionSet>()) {}
        AdaptiveActionSet(std::shared_ptr<::AdaptiveCards::ActionSet> const& sharedActionSet);

        property < winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement>> Actions;

        auto ElementType() { return Uwp::ElementType::ActionSet; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveActionSet : AdaptiveActionSetT<AdaptiveActionSet, implementation::AdaptiveActionSet>
    {
    };
}
