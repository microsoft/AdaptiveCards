// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveActionEventArgs.g.h"

namespace rtobjects = winrt::AdaptiveCards::ObjectModel::WinUI3;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveActionEventArgs : AdaptiveActionEventArgsT<AdaptiveActionEventArgs>
    {
        AdaptiveActionEventArgs(rtobjects::IAdaptiveActionElement const& action, WinUI3::AdaptiveInputs const& inputs) :
            Action{action},
            Inputs{inputs}
        {

        }

        property<rtobjects::IAdaptiveActionElement> Action;
        property<WinUI3::AdaptiveInputs> Inputs;
    };
}
