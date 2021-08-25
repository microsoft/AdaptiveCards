// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageConfig.h"
#include "AdaptiveImageConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveImageConfig::AdaptiveImageConfig(::AdaptiveCards::ImageConfig sharedImageConfig)
    {
        ImageSize = static_cast<ObjectModel::WinUI3::ImageSize>(sharedImageConfig.imageSize);
    }
}
