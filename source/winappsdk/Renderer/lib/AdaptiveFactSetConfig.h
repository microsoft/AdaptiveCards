// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFactSetConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveFactSetConfig : AdaptiveFactSetConfigT < AdaptiveFactSetConfig>
    {
        AdaptiveFactSetConfig(::AdaptiveCards::FactSetConfig factSetConfig = {});

        property<WinUI3::AdaptiveFactSetTextConfig> Title;
        property<WinUI3::AdaptiveFactSetTextConfig> Value;
        property<uint32_t> Spacing;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveFactSetConfig : AdaptiveFactSetConfigT<AdaptiveFactSetConfig, implementation::AdaptiveFactSetConfig>
    {
    };
}
