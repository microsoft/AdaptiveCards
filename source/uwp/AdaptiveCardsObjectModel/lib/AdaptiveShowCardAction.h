// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ShowCardAction.h"
#include "AdaptiveActionElement.h"
#include "AdaptiveShowCardAction.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("429d6be9-a5f4-44dc-8dc3-3fe9b633ff1c") AdaptiveShowCardAction : AdaptiveShowCardActionT<AdaptiveShowCardAction, ITypePeek>, AdaptiveActionElementBase
    {
        AdaptiveShowCardAction(const std::shared_ptr<::AdaptiveCards::ShowCardAction>& sharedShowCardAction =
                                   std::make_shared<::AdaptiveCards::ShowCardAction>());

        property<Uwp::AdaptiveCard> Card{nullptr};

        auto ActionType() { return ActionType::ShowCard; }

        virtual std::shared_ptr<::AdaptiveCards::BaseActionElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveShowCardAction : AdaptiveShowCardActionT<AdaptiveShowCardAction, implementation::AdaptiveShowCardAction>
    {
    };
}
