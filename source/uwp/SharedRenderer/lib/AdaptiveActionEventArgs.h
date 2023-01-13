// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveActionEventArgs.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveActionEventArgs : AdaptiveActionEventArgsT<AdaptiveActionEventArgs>
    {
        AdaptiveActionEventArgs(winrt::IAdaptiveActionElement const& action, winrt::AdaptiveInputs const& inputs) :
            Action{action}, Inputs{inputs}
        {
        }

        property<winrt::IAdaptiveActionElement> Action;
        property<winrt::AdaptiveInputs> Inputs;
    };
}
