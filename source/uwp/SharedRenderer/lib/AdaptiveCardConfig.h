// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCardConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveCardConfig : AdaptiveCardConfigT<AdaptiveCardConfig>
    {
        AdaptiveCardConfig(::AdaptiveCards::AdaptiveCardConfig const& adaptiveCardConfig = {});

        property<bool> AllowCustomStyle;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveCardConfig : AdaptiveCardConfigT<AdaptiveCardConfig, implementation::AdaptiveCardConfig>
    {
    };
}
