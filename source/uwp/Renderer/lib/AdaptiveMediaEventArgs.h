// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveMediaEventArgs.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveMediaEventArgs : AdaptiveMediaEventArgsT<AdaptiveMediaEventArgs>
    {
        AdaptiveMediaEventArgs(ObjectModel::Uwp::AdaptiveMedia const& media = nullptr) : Media{media} {}
        property<ObjectModel::Uwp::AdaptiveMedia> Media;
    };
}
