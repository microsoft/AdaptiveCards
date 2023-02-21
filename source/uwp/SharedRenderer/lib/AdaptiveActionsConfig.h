// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveActionsConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveActionsConfig : AdaptiveActionsConfigT<AdaptiveActionsConfig>
    {
        AdaptiveActionsConfig(::AdaptiveCards::ActionsConfig const& actionsConfig = {});

        property<winrt::AdaptiveShowCardActionConfig> ShowCard;
        property<winrt::ActionsOrientation> ActionsOrientation;
        property<winrt::ActionAlignment> ActionAlignment;
        property<uint32_t> ButtonSpacing;
        property<uint32_t> MaxActions;
        property<winrt::Spacing> Spacing;
        property<winrt::IconPlacement> IconPlacement;
        property<uint32_t> IconSize;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveActionsConfig : AdaptiveActionsConfigT<AdaptiveActionsConfig, implementation::AdaptiveActionsConfig>
    {
    };
}
