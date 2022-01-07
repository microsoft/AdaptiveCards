// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveImageSetConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveImageSetConfig : AdaptiveImageSetConfigT<AdaptiveImageSetConfig>
    {
        AdaptiveImageSetConfig(::AdaptiveCards::ImageSetConfig const& ImageSetConfig = {});

        property<winrt::ImageSize> ImageSize;
        property<uint32_t> MaxImageHeight;
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveImageSetConfig : AdaptiveImageSetConfigT<AdaptiveImageSetConfig, implementation::AdaptiveImageSetConfig>
    {
    };
}
