// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCardConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveCardConfig : AdaptiveCardConfigT<AdaptiveCardConfig>
    {
        AdaptiveCardConfig(::AdaptiveCards::AdaptiveCardConfig const& adaptiveCardConfig = {});

        property<bool> AllowCustomStyle;
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveCardConfig : AdaptiveCardConfigT<AdaptiveCardConfig, implementation::AdaptiveCardConfig>
    {
    };
}
