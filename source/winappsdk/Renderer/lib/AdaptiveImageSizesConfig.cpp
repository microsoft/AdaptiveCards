// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageSizesConfig.h"
#include "AdaptiveImageSizesConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveImageSizesConfig::AdaptiveImageSizesConfig(::AdaptiveCards::ImageSizesConfig imageSizesConfig)
    {
        Small = imageSizesConfig.smallSize;
        Medium = imageSizesConfig.mediumSize;
        Large = imageSizesConfig.largeSize;
    }
}
