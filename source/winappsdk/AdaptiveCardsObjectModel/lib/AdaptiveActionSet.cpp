// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionSet.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation::Collections;

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
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
