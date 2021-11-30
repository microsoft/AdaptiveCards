// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageSizesConfig.h"
#include "AdaptiveImageSizesConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    AdaptiveImageSizesConfig::AdaptiveImageSizesConfig(::AdaptiveCards::ImageSizesConfig const& imageSizesConfig)
    {
        Small = imageSizesConfig.smallSize;
        Medium = imageSizesConfig.mediumSize;
        Large = imageSizesConfig.largeSize;
    }
}
