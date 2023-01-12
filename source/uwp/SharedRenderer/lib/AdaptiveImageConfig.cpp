// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageConfig.h"
#include "AdaptiveImageConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveImageConfig::AdaptiveImageConfig(::AdaptiveCards::ImageConfig const& sharedImageConfig)
    {
        ImageSize = static_cast<winrt::ImageSize>(sharedImageConfig.imageSize);
    }
}
