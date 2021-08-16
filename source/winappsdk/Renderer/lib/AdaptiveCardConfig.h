// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCardConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveCardConfig : AdaptiveCardConfigT < AdaptiveCardConfig>
    {
        AdaptiveCardConfig(::AdaptiveCards::AdaptiveCardConfig adaptiveCardConfig = {});

        property<bool> AllowCustomStyle;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveCardConfig : AdaptiveCardConfigT<AdaptiveCardConfig, implementation::AdaptiveCardConfig>
    {
    };
}
