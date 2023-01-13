// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFontSizesConfig.h"
#include "AdaptiveFontSizesConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveFontSizesConfig::AdaptiveFontSizesConfig(::AdaptiveCards::FontSizesConfig const& fontSizesConfig)
    {
        Default = fontSizesConfig.GetFontSize(::AdaptiveCards::TextSize::Default);
        Small = fontSizesConfig.GetFontSize(::AdaptiveCards::TextSize::Small);
        Medium = fontSizesConfig.GetFontSize(::AdaptiveCards::TextSize::Medium);
        Large = fontSizesConfig.GetFontSize(::AdaptiveCards::TextSize::Large);
        ExtraLarge = fontSizesConfig.GetFontSize(::AdaptiveCards::TextSize::ExtraLarge);
    }
}
