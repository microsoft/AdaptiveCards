// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveActionEventArgs.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveActionEventArgs : AdaptiveActionEventArgsT<AdaptiveActionEventArgs>
    {
        AdaptiveActionEventArgs(winrt::IAdaptiveActionElement const& action, Uwp::AdaptiveInputs const& inputs) :
            Action{action}, Inputs{inputs}
        {
        }

        property<winrt::IAdaptiveActionElement> Action;
        property<Uwp::AdaptiveInputs> Inputs;
    };
}
