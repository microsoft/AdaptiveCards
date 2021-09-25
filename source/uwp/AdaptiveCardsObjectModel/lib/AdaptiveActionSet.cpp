// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionSet.h"
#include "AdaptiveActionSet.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveActionSet::AdaptiveActionSet(std::shared_ptr<::AdaptiveCards::ActionSet> const& sharedActionSet)
    {
        Actions = GenerateActionsProjection(sharedActionSet->GetActions());
        InitializeBaseElement(sharedActionSet);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveActionSet::GetSharedModel()
    {
        auto actionSet = std::make_shared<::AdaptiveCards::ActionSet>();
        CopySharedElementProperties(*actionSet);

        actionSet->GetActions() = GenerateSharedActions(Actions.get());

        return actionSet;
    }
}
