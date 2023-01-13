// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTextStyleConfig.h"
#include "AdaptiveFactSetTextConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveFactSetTextConfig : AdaptiveFactSetTextConfigT<AdaptiveFactSetTextConfig>, AdaptiveTextStyleConfigBase
    {
        AdaptiveFactSetTextConfig(::AdaptiveCards::FactSetTextConfig const& textConfig = {});

        property<bool> Wrap;
        property<uint32_t> MaxWidth;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveFactSetTextConfig : AdaptiveFactSetTextConfigT<AdaptiveFactSetTextConfig, implementation::AdaptiveFactSetTextConfig>
    {
    };
}
