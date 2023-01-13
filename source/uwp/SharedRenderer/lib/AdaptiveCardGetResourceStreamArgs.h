// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCardGetResourceStreamArgs.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveCardGetResourceStreamArgs : AdaptiveCardGetResourceStreamArgsT<AdaptiveCardGetResourceStreamArgs>
    {
        AdaptiveCardGetResourceStreamArgs(winrt::Uri const& url = nullptr) : Url{url} {}

        property<winrt::Uri> Url;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveCardGetResourceStreamArgs
        : AdaptiveCardGetResourceStreamArgsT<AdaptiveCardGetResourceStreamArgs, implementation::AdaptiveCardGetResourceStreamArgs>
    {
    };
}
