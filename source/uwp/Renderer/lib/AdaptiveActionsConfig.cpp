// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionsConfig.h"
#include "AdaptiveShowCardActionConfig.h"
#include "AdaptiveActionsConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    AdaptiveActionsConfig::AdaptiveActionsConfig(::AdaptiveCards::ActionsConfig actionsConfig) :
        ShowCard{winrt::make<implementation::AdaptiveShowCardActionConfig>(actionsConfig.showCard)}
    {
        ActionsOrientation = static_cast<Uwp::ActionsOrientation>(actionsConfig.actionsOrientation);
        ActionAlignment = static_cast<Uwp::ActionAlignment>(actionsConfig.actionAlignment);
        ButtonSpacing = actionsConfig.buttonSpacing;
        MaxActions = actionsConfig.maxActions;
        Spacing = static_cast<ObjectModel::Uwp::Spacing>(actionsConfig.spacing);
        IconPlacement = static_cast<Uwp::IconPlacement>(actionsConfig.iconPlacement);
        IconSize = actionsConfig.iconSize;
    }
}
