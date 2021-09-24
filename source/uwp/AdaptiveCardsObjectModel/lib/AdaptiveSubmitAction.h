// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "SubmitAction.h"
#include "AdaptiveActionElement.h"
#include "AdaptiveSubmitAction.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("32114ce2-7e10-4f7f-8225-bfd661c6794c") AdaptiveSubmitAction : AdaptiveSubmitActionT<AdaptiveSubmitAction, ITypePeek>, AdaptiveActionElementBase
    {
        AdaptiveSubmitAction(const std::shared_ptr<::AdaptiveCards::SubmitAction>& sharedSubmitAction =
                                 std::make_shared<::AdaptiveCards::SubmitAction>());

        // IAdaptiveSubmitAction
        property<winrt::Windows::Data::Json::JsonValue> DataJson{nullptr};
        property<Uwp::AssociatedInputs> AssociatedInputs;

        // IAdaptiveActionElement
        auto ActionType() { return ActionType::Submit; }

        std::shared_ptr<::AdaptiveCards::BaseActionElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveSubmitAction : AdaptiveSubmitActionT<AdaptiveSubmitAction, implementation::AdaptiveSubmitAction>
    {
    };
}
