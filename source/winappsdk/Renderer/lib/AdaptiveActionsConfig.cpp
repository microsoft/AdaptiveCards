// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionsConfig.h"
#include "AdaptiveShowCardActionConfig.h"
#include "AdaptiveActionsConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveActionsConfig::AdaptiveActionsConfig(::AdaptiveCards::ActionsConfig actionsConfig) :
        ShowCard{winrt::make<implementation::AdaptiveShowCardActionConfig>(actionsConfig.showCard)}
    {
        ActionsOrientation = static_cast<WinUI3::ActionsOrientation>(actionsConfig.actionsOrientation);
        ActionAlignment = static_cast<WinUI3::ActionAlignment>(actionsConfig.actionAlignment);
        ButtonSpacing = actionsConfig.buttonSpacing;
        MaxActions = actionsConfig.maxActions;
        Spacing = static_cast<ObjectModel::WinUI3::Spacing>(actionsConfig.spacing);
        IconPlacement = static_cast<WinUI3::IconPlacement>(actionsConfig.iconPlacement);
        IconSize = actionsConfig.iconSize;
    }
}
