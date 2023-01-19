// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveMediaEventArgs.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveMediaEventArgs : AdaptiveMediaEventArgsT<AdaptiveMediaEventArgs>
    {
        AdaptiveMediaEventArgs(winrt::AdaptiveMedia const& media = nullptr) : Media{media} {}
        property<winrt::AdaptiveMedia> Media;
    };
}
