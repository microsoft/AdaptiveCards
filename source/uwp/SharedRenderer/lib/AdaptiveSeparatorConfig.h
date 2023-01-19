// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveSeparatorConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveSeparatorConfig : AdaptiveSeparatorConfigT<AdaptiveSeparatorConfig>
    {
        AdaptiveSeparatorConfig(::AdaptiveCards::SeparatorConfig const& SeparatorConfig = {});

        property<uint32_t> LineThickness;
        property<winrt::Windows::UI::Color> LineColor;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveSeparatorConfig : AdaptiveSeparatorConfigT<AdaptiveSeparatorConfig, AdaptiveSeparatorConfig>
    {
    };
}
