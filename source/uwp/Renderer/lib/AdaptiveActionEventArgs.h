// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveActionEventArgs.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveActionEventArgs : AdaptiveActionEventArgsT<AdaptiveActionEventArgs>
    {
        AdaptiveActionEventArgs(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& action, Uwp::AdaptiveInputs const& inputs) :
            Action{action}, Inputs{inputs}
        {
        }

        property<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement> Action;
        property<Uwp::AdaptiveInputs> Inputs;
    };
}
