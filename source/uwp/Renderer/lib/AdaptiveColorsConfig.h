// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveColorsConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveColorsConfig : AdaptiveColorsConfigT<AdaptiveColorsConfig>
    {
        AdaptiveColorsConfig(::AdaptiveCards::ColorsConfig colorsConfig = {});

        property<winrt::AdaptiveCards::Rendering::Uwp::AdaptiveColorConfig> Default;
        property<winrt::AdaptiveCards::Rendering::Uwp::AdaptiveColorConfig> Accent;
        property<winrt::AdaptiveCards::Rendering::Uwp::AdaptiveColorConfig> Dark;
        property<winrt::AdaptiveCards::Rendering::Uwp::AdaptiveColorConfig> Light;
        property<winrt::AdaptiveCards::Rendering::Uwp::AdaptiveColorConfig> Good;
        property<winrt::AdaptiveCards::Rendering::Uwp::AdaptiveColorConfig> Warning;
        property<winrt::AdaptiveCards::Rendering::Uwp::AdaptiveColorConfig> Attention;
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveColorsConfig : AdaptiveColorsConfigT<AdaptiveColorsConfig, implementation::AdaptiveColorsConfig>
    {
    };
}
