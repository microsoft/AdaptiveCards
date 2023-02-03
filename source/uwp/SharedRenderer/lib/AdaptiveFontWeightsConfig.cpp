// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFontWeightsConfig.h"
#include "AdaptiveFontWeightsConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveFontWeightsConfig::AdaptiveFontWeightsConfig(::AdaptiveCards::FontWeightsConfig const& fontWeightsConfig)
    {
        Default = static_cast<uint16_t>(fontWeightsConfig.GetFontWeight(::AdaptiveCards::TextWeight::Default));
        Lighter = static_cast<uint16_t>(fontWeightsConfig.GetFontWeight(::AdaptiveCards::TextWeight::Lighter));
        Bolder = static_cast<uint16_t>(fontWeightsConfig.GetFontWeight(::AdaptiveCards::TextWeight::Bolder));
    }
}
