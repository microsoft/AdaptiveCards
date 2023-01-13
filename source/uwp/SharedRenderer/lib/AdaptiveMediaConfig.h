// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveMediaConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveMediaConfig : AdaptiveMediaConfigT<AdaptiveMediaConfig>
    {
        AdaptiveMediaConfig(::AdaptiveCards::MediaConfig const& mediaConfig = {});

        property<hstring> DefaultPoster;
        property<hstring> PlayButton;
        property<bool> AllowInlinePlayback;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveMediaConfig : AdaptiveMediaConfigT<AdaptiveMediaConfig, implementation::AdaptiveMediaConfig>
    {
    };
}
