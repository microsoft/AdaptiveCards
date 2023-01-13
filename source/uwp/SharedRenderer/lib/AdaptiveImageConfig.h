// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveImageConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveImageConfig : AdaptiveImageConfigT<AdaptiveImageConfig>
    {
        AdaptiveImageConfig(::AdaptiveCards::ImageConfig const& ImageConfig = {});

        property<winrt::ImageSize> ImageSize;
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveImageConfig : AdaptiveImageConfigT<AdaptiveImageConfig, implementation::AdaptiveImageConfig>
    {
    };
}
