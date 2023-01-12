// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveColorsConfig.h"
#include "AdaptiveColorConfig.h"
#include "AdaptiveColorsConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveColorsConfig::AdaptiveColorsConfig(::AdaptiveCards::ColorsConfig colorsConfig)
    {
        Default = winrt::make<implementation::AdaptiveColorConfig>(colorsConfig.defaultColor);
        Accent = winrt::make<implementation::AdaptiveColorConfig>(colorsConfig.accent);
        Attention = winrt::make<implementation::AdaptiveColorConfig>(colorsConfig.attention);
        Dark = winrt::make<implementation::AdaptiveColorConfig>(colorsConfig.dark);
        Good = winrt::make<implementation::AdaptiveColorConfig>(colorsConfig.good);
        Light = winrt::make<implementation::AdaptiveColorConfig>(colorsConfig.light);
        Warning = winrt::make<implementation::AdaptiveColorConfig>(colorsConfig.warning);
    }
}
