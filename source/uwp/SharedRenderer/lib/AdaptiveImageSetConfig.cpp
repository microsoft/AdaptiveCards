// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageSetConfig.h"
#include "AdaptiveImageSetConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveImageSetConfig::AdaptiveImageSetConfig(::AdaptiveCards::ImageSetConfig const& sharedImageSetConfig)
    {
        ImageSize = static_cast<winrt::ImageSize>(sharedImageSetConfig.imageSize);
        MaxImageHeight = sharedImageSetConfig.maxImageHeight;
    }
}
