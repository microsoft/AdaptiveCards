// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTextStyleConfigBase.h"
#include "AdaptiveTextStyleConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveTextStyleConfig : AdaptiveTextStyleConfigT<AdaptiveTextStyleConfig>, AdaptiveTextStyleConfigBase
    {
        AdaptiveTextStyleConfig(::AdaptiveCards::TextStyleConfig const& textConfig = {}) :
            AdaptiveTextStyleConfigBase(textConfig)
        {
        }
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveTextStyleConfig : AdaptiveTextStyleConfigT<AdaptiveTextStyleConfig, implementation::AdaptiveTextStyleConfig>
    {
    };
}
