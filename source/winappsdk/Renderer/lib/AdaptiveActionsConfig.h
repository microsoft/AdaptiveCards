// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveActionsConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveActionsConfig : AdaptiveActionsConfigT < AdaptiveActionsConfig>
    {
        AdaptiveActionsConfig(::AdaptiveCards::ActionsConfig actionsConfig = {});

        property<WinUI3::AdaptiveShowCardActionConfig> ShowCard;
        property<WinUI3::ActionsOrientation> ActionsOrientation;
        property<WinUI3::ActionAlignment> ActionAlignment;
        property<uint32_t> ButtonSpacing;
        property<uint32_t> MaxActions;
        property<ObjectModel::WinUI3::Spacing> Spacing;
        property<WinUI3::IconPlacement> IconPlacement;
        property<uint32_t> IconSize;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveActionsConfig : AdaptiveActionsConfigT<AdaptiveActionsConfig, implementation::AdaptiveActionsConfig>
    {
    };
}
