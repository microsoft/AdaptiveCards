// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveActionsConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveActionsConfig : AdaptiveActionsConfigT < AdaptiveActionsConfig>
    {
        AdaptiveActionsConfig(::AdaptiveCards::ActionsConfig actionsConfig = {});

        property<Uwp::AdaptiveShowCardActionConfig> ShowCard;
        property<Uwp::ActionsOrientation> ActionsOrientation;
        property<Uwp::ActionAlignment> ActionAlignment;
        property<uint32_t> ButtonSpacing;
        property<uint32_t> MaxActions;
        property<ObjectModel::Uwp::Spacing> Spacing;
        property<Uwp::IconPlacement> IconPlacement;
        property<uint32_t> IconSize;
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveActionsConfig : AdaptiveActionsConfigT<AdaptiveActionsConfig, implementation::AdaptiveActionsConfig>
    {
    };
}
