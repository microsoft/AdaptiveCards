// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ToggleVisibilityTarget.h"
#include "AdaptiveToggleVisibilityTarget.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("d37e5b66-2a5e-4a9e-b087-dbef5a1705b1") AdaptiveToggleVisibilityTarget
        : AdaptiveToggleVisibilityTargetT<AdaptiveToggleVisibilityTarget, ITypePeek>
    {
        AdaptiveToggleVisibilityTarget() :
            AdaptiveToggleVisibilityTarget(std::make_shared<::AdaptiveCards::ToggleVisibilityTarget>())
        {
        }

        AdaptiveToggleVisibilityTarget(std::shared_ptr<::AdaptiveCards::ToggleVisibilityTarget> const& sharedToggleTarget);

        property<hstring> ElementId;
        property<Uwp::IsVisible> IsVisible;

        std::shared_ptr<::AdaptiveCards::ToggleVisibilityTarget> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveToggleVisibilityTarget
        : AdaptiveToggleVisibilityTargetT<AdaptiveToggleVisibilityTarget, implementation::AdaptiveToggleVisibilityTarget>
    {
    };
}
