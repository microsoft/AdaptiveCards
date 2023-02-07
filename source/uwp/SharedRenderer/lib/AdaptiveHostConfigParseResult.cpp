// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveHostConfigParseResult.h"
#include "AdaptiveHostConfigParseResult.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveHostConfigParseResult::AdaptiveHostConfigParseResult(winrt::AdaptiveHostConfig const& value) :
        Errors{winrt::single_threaded_vector<winrt::AdaptiveError>()}, HostConfig{value}
    {
    }
}
