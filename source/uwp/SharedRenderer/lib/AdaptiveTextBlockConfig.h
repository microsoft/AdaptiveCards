// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTextBlockConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveTextBlockConfig : AdaptiveTextBlockConfigT<AdaptiveTextBlockConfig>
    {
        AdaptiveTextBlockConfig(::AdaptiveCards::TextBlockConfig const& textBlockConfig = {});

        property<uint32_t> HeadingLevel;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveTextBlockConfig : AdaptiveTextBlockConfigT<AdaptiveTextBlockConfig, implementation::AdaptiveTextBlockConfig>
    {
    };
}
