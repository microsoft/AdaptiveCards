// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveSeparatorConfig.h"
#include "AdaptiveSeparatorConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveSeparatorConfig::AdaptiveSeparatorConfig(::AdaptiveCards::SeparatorConfig const& sharedSeparatorConfig)
    {
        LineColor = GetColorFromString(sharedSeparatorConfig.lineColor);
        LineThickness = sharedSeparatorConfig.lineThickness;
    }
}
