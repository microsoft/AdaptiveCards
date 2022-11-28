// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveHostConfigParseResult.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveHostConfigParseResult : AdaptiveHostConfigParseResultT<AdaptiveHostConfigParseResult>
    {
        AdaptiveHostConfigParseResult(winrt::render_xaml::AdaptiveHostConfig const& hostConfig = nullptr);

        property<winrt::render_xaml::AdaptiveHostConfig> HostConfig;
        property<winrt::IVector<winrt::AdaptiveError>> Errors;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveHostConfigParseResult
        : AdaptiveHostConfigParseResultT<AdaptiveHostConfigParseResult, implementation::AdaptiveHostConfigParseResult>
    {
    };
}
