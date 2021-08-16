// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveColorsConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveColorsConfig : AdaptiveColorsConfigT<AdaptiveColorsConfig>
    {
        AdaptiveColorsConfig(::AdaptiveCards::ColorsConfig colorsConfig = {});

        property<winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveColorConfig> Default;
        property<winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveColorConfig> Accent;
        property<winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveColorConfig> Dark;
        property<winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveColorConfig> Light;
        property<winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveColorConfig> Good;
        property<winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveColorConfig> Warning;
        property<winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveColorConfig> Attention;
    };
}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveColorsConfig : AdaptiveColorsConfigT<AdaptiveColorsConfig, implementation::AdaptiveColorsConfig>
    {
    };
}
