// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "UnknownAction.h"
#include "AdaptiveActionElement.h"
#include "AdaptiveUnsupportedAction.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("D5018CF5-97D9-4FC4-88E8-9415D51431B6") AdaptiveUnsupportedAction
        : AdaptiveUnsupportedActionT<AdaptiveUnsupportedAction, ITypePeek>,
          AdaptiveActionElementBase
    {
        AdaptiveUnsupportedAction(const std::shared_ptr<::AdaptiveCards::UnknownAction>& sharedUnknownAction =
                                      std::make_shared<::AdaptiveCards::UnknownAction>());

        auto ActionType() { return Uwp::ActionType::Unsupported; }

        std::shared_ptr<::AdaptiveCards::BaseActionElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveUnsupportedAction : AdaptiveUnsupportedActionT<AdaptiveUnsupportedAction, implementation::AdaptiveUnsupportedAction>
    {
    };
}
