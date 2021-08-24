// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveMediaEventArgs.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveMediaEventArgs : AdaptiveMediaEventArgsT < AdaptiveMediaEventArgs>
    {
        AdaptiveMediaEventArgs(ObjectModel::WinUI3::AdaptiveMedia const& media = nullptr) : Media{media} {}
        property<ObjectModel::WinUI3::AdaptiveMedia> Media;
    };
}
