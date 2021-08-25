// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageSetConfig.h"
#include "AdaptiveImageSetConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveImageSetConfig::AdaptiveImageSetConfig(::AdaptiveCards::ImageSetConfig sharedImageSetConfig)
    {
        ImageSize = static_cast<ObjectModel::WinUI3::ImageSize>(sharedImageSetConfig.imageSize);
        MaxImageHeight = sharedImageSetConfig.maxImageHeight;
    }
}
