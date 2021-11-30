// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageConfig.h"
#include "AdaptiveImageConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    AdaptiveImageConfig::AdaptiveImageConfig(::AdaptiveCards::ImageConfig sharedImageConfig)
    {
        ImageSize = static_cast<ObjectModel::Uwp::ImageSize>(sharedImageConfig.imageSize);
    }
}
