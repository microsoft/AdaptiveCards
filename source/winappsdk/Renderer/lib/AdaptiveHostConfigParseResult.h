// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "util.h"

#include "AdaptiveHostConfigParseResult.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveHostConfigParseResult : AdaptiveHostConfigParseResultT<AdaptiveHostConfigParseResult>
    {
        AdaptiveHostConfigParseResult(WinUI3::AdaptiveHostConfig const& hostConfig = nullptr);

        property<WinUI3::AdaptiveHostConfig> HostConfig;
        property<winrt::Windows::Foundation::Collections::IVector<ObjectModel::WinUI3::AdaptiveError>> Errors;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveHostConfigParseResult
        : AdaptiveHostConfigParseResultT<AdaptiveHostConfigParseResult, implementation::AdaptiveHostConfigParseResult>
    {
    };
}
