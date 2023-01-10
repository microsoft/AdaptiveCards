// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveImageSizesConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveImageSizesConfig : AdaptiveImageSizesConfigT<AdaptiveImageSizesConfig>
    {
        AdaptiveImageSizesConfig(::AdaptiveCards::ImageSizesConfig const& imageSizesConfig = {});

        property<uint32_t> Small;
        property<uint32_t> Medium;
        property<uint32_t> Large;
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveImageSizesConfig : AdaptiveImageSizesConfigT<AdaptiveImageSizesConfig, implementation::AdaptiveImageSizesConfig>
    {
    };
}
