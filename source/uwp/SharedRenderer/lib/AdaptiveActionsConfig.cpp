// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionsConfig.h"
#include "AdaptiveShowCardActionConfig.h"
#include "AdaptiveActionsConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveActionsConfig::AdaptiveActionsConfig(::AdaptiveCards::ActionsConfig const& actionsConfig) :
        ShowCard{winrt::make<winrt::implementation::AdaptiveShowCardActionConfig>(actionsConfig.showCard)}
    {
        ActionsOrientation = static_cast<winrt::ActionsOrientation>(actionsConfig.actionsOrientation);
        ActionAlignment = static_cast<winrt::ActionAlignment>(actionsConfig.actionAlignment);
        ButtonSpacing = actionsConfig.buttonSpacing;
        MaxActions = actionsConfig.maxActions;
        Spacing = static_cast<winrt::Spacing>(actionsConfig.spacing);
        IconPlacement = static_cast<winrt::IconPlacement>(actionsConfig.iconPlacement);
        IconSize = actionsConfig.iconSize;
    }
}
