// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ToggleVisibilityAction.h"
#include "AdaptiveActionElement.h"
#include "AdaptiveToggleVisibilityAction.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("32114ce2-7e10-4f7f-8225-bfd661c6794c") AdaptiveToggleVisibilityAction
        : AdaptiveToggleVisibilityActionT<AdaptiveToggleVisibilityAction, ITypePeek>,
          AdaptiveActionElementBase
    {
        AdaptiveToggleVisibilityAction() :
            AdaptiveToggleVisibilityAction(std::make_shared<::AdaptiveCards::ToggleVisibilityAction>())
        {
        }

        AdaptiveToggleVisibilityAction(std::shared_ptr<::AdaptiveCards::ToggleVisibilityAction> const& sharedToggleVisibilityAction);

        // IAdaptiveToggleVisibilityAction
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveToggleVisibilityTarget>> TargetElements;

        // IAdaptiveActionElement
        winrt::AdaptiveCards::ObjectModel::Uwp::ActionType ActionType();

        virtual std::shared_ptr<::AdaptiveCards::BaseActionElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveToggleVisibilityAction : AdaptiveToggleVisibilityActionT<AdaptiveToggleVisibilityAction, implementation::AdaptiveToggleVisibilityAction>
    {
    };
}
