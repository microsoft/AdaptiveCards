// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveToggleVisibilityTarget.h"
#include "AdaptiveToggleVisibilityTarget.g.cpp"
#include "ToggleVisibilityTarget.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveToggleVisibilityTarget::AdaptiveToggleVisibilityTarget(const std::shared_ptr<::AdaptiveCards::ToggleVisibilityTarget>& sharedToggleTarget)
    {
        ElementId = UTF8ToHString(sharedToggleTarget->GetElementId());
        IsVisible = static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::IsVisible>(sharedToggleTarget->GetIsVisible());
    }

    std::shared_ptr<::AdaptiveCards::ToggleVisibilityTarget> AdaptiveToggleVisibilityTarget::GetSharedModel()
    {
        auto toggleTarget = std::make_shared<::AdaptiveCards::ToggleVisibilityTarget>();
        toggleTarget->SetElementId(HStringToUTF8(ElementId));
        toggleTarget->SetIsVisible(static_cast<::AdaptiveCards::IsVisible>(IsVisible.get()));
        return toggleTarget;
    }
}
