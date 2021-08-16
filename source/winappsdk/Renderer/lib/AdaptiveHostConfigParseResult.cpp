// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveHostConfigParseResult.h"
#include "AdaptiveHostConfigParseResult.g.cpp"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveHostConfigParseResult::AdaptiveHostConfigParseResult(WinUI3::AdaptiveHostConfig const& value) :
        Errors{winrt::single_threaded_vector<ObjectModel::WinUI3::AdaptiveError>()}
    {
        HostConfig = value;
    }
}
