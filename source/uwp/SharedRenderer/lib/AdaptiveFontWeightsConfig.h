// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFontWeightsConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveFontWeightsConfig : AdaptiveFontWeightsConfigT<AdaptiveFontWeightsConfig>
    {
        AdaptiveFontWeightsConfig(::AdaptiveCards::FontWeightsConfig const& fontWeightsConfig = {});

        property<uint16_t> Lighter;
        property<uint16_t> Default;
        property<uint16_t> Bolder;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveFontWeightsConfig : AdaptiveFontWeightsConfigT<AdaptiveFontWeightsConfig, implementation::AdaptiveFontWeightsConfig>
    {
    };
}
