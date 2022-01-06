// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveHostConfigParseResult.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveHostConfigParseResult : AdaptiveHostConfigParseResultT<AdaptiveHostConfigParseResult>
    {
        AdaptiveHostConfigParseResult(Uwp::AdaptiveHostConfig const& hostConfig = nullptr);

        property<Uwp::AdaptiveHostConfig> HostConfig;
        property<winrt::IVector<ObjectModel::Uwp::AdaptiveError>> Errors;
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveHostConfigParseResult
        : AdaptiveHostConfigParseResultT<AdaptiveHostConfigParseResult, implementation::AdaptiveHostConfigParseResult>
    {
    };
}
