// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveMediaConfig.h"
#include "AdaptiveMediaConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveMediaConfig::AdaptiveMediaConfig(::AdaptiveCards::MediaConfig const& mediaConfig)
    {
        DefaultPoster = UTF8ToHString(mediaConfig.defaultPoster);
        PlayButton = UTF8ToHString(mediaConfig.playButton);
        AllowInlinePlayback = mediaConfig.allowInlinePlayback;
    }
}
