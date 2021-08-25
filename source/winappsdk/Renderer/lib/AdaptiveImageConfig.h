// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveImageConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveImageConfig : AdaptiveImageConfigT < AdaptiveImageConfig>
    {
        AdaptiveImageConfig(::AdaptiveCards::ImageConfig ImageConfig = {});

        property<ObjectModel::WinUI3::ImageSize> ImageSize;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveImageConfig : AdaptiveImageConfigT<AdaptiveImageConfig, implementation::AdaptiveImageConfig>
    {
    };
}
