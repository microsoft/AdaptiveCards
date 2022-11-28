// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveColorsConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveColorsConfig : AdaptiveColorsConfigT<AdaptiveColorsConfig>
    {
        AdaptiveColorsConfig(::AdaptiveCards::ColorsConfig colorsConfig = {});

        property<winrt::render_xaml::AdaptiveColorConfig> Default;
        property<winrt::render_xaml::AdaptiveColorConfig> Accent;
        property<winrt::render_xaml::AdaptiveColorConfig> Dark;
        property<winrt::render_xaml::AdaptiveColorConfig> Light;
        property<winrt::render_xaml::AdaptiveColorConfig> Good;
        property<winrt::render_xaml::AdaptiveColorConfig> Warning;
        property<winrt::render_xaml::AdaptiveColorConfig> Attention;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveColorsConfig : AdaptiveColorsConfigT<AdaptiveColorsConfig, implementation::AdaptiveColorsConfig>
    {
    };
}
