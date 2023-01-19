// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFactSetConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveFactSetConfig : AdaptiveFactSetConfigT<AdaptiveFactSetConfig>
    {
        AdaptiveFactSetConfig(::AdaptiveCards::FactSetConfig const& factSetConfig = {});

        property<winrt::AdaptiveFactSetTextConfig> Title;
        property<winrt::AdaptiveFactSetTextConfig> Value;
        property<uint32_t> Spacing;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveFactSetConfig : AdaptiveFactSetConfigT<AdaptiveFactSetConfig, implementation::AdaptiveFactSetConfig>
    {
    };
}
