// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveImageSetConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveImageSetConfig : AdaptiveImageSetConfigT < AdaptiveImageSetConfig>
    {
        AdaptiveImageSetConfig(::AdaptiveCards::ImageSetConfig ImageSetConfig = {});

        property<ObjectModel::WinUI3::ImageSize> ImageSize;
        property<uint32_t> MaxImageHeight;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveImageSetConfig : AdaptiveImageSetConfigT<AdaptiveImageSetConfig, implementation::AdaptiveImageSetConfig>
    {
    };
}
