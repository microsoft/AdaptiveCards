// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "OpenUrlAction.h"
#include "AdaptiveActionElement.h"
#include "AdaptiveOpenUrlAction.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("96c1ded5-1ef8-4aa8-8ccf-0bea96295ac8") AdaptiveOpenUrlAction : AdaptiveOpenUrlActionT<AdaptiveOpenUrlAction, ITypePeek>, AdaptiveActionElementBase
    {
        AdaptiveOpenUrlAction(const std::shared_ptr<::AdaptiveCards::OpenUrlAction>& sharedOpenUrlAction =
                                  std::make_shared<::AdaptiveCards::OpenUrlAction>());

        // IAdaptiveOpenUrlAction
        property<winrt::Windows::Foundation::Uri> Url{nullptr};

        // IAdaptiveActionElement
        auto ActionType() { return ActionType::OpenUrl; }

        virtual std::shared_ptr<::AdaptiveCards::BaseActionElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveOpenUrlAction : AdaptiveOpenUrlActionT<AdaptiveOpenUrlAction, implementation::AdaptiveOpenUrlAction>
    {
    };
}
