// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveColorConfig.h"
#include "AdaptiveHighlightColorConfig.h"
#include "AdaptiveColorConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveColorConfig::AdaptiveColorConfig(::AdaptiveCards::ColorConfig colorConfig)
    {
        Default = GetColorFromString(colorConfig.defaultColor);
        Subtle = GetColorFromString(colorConfig.subtleColor);
        HighlightColors = winrt::make<implementation::AdaptiveHighlightColorConfig>(colorConfig.highlightColors);
    }
}
