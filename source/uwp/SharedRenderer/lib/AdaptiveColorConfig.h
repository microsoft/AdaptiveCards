// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveColorConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveColorConfig : AdaptiveColorConfigT<AdaptiveColorConfig>
    {
    public:
        AdaptiveColorConfig(::AdaptiveCards::ColorConfig colorConfig = {});

        property<winrt::Windows::UI::Color> Default;
        property<winrt::Windows::UI::Color> Subtle;
        property<winrt::AdaptiveHighlightColorConfig> HighlightColors;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveColorConfig : AdaptiveColorConfigT<AdaptiveColorConfig, implementation::AdaptiveColorConfig>
    {
    };
}
