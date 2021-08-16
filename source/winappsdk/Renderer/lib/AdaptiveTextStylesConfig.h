// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTextStylesConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveTextStylesConfig : AdaptiveTextStylesConfigT < AdaptiveTextStylesConfig>
    {
        AdaptiveTextStylesConfig(::AdaptiveCards::TextStylesConfig const& textConfig = {});

        property<WinUI3::AdaptiveTextStyleConfig> Heading;
        property<WinUI3::AdaptiveTextStyleConfig> ColumnHeader;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveTextStylesConfig : AdaptiveTextStylesConfigT<AdaptiveTextStylesConfig, implementation::AdaptiveTextStylesConfig>
    {
    };
}
