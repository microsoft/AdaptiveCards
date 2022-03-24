// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTextStylesConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveTextStylesConfig : AdaptiveTextStylesConfigT<AdaptiveTextStylesConfig>
    {
        AdaptiveTextStylesConfig(::AdaptiveCards::TextStylesConfig const& textConfig = {});

        property<winrt::AdaptiveTextStyleConfig> Heading;
        property<winrt::AdaptiveTextStyleConfig> ColumnHeader;
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveTextStylesConfig : AdaptiveTextStylesConfigT<AdaptiveTextStylesConfig, implementation::AdaptiveTextStylesConfig>
    {
    };
}
