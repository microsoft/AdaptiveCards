// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardParseResult.h"
#include "AdaptiveCardParseResult.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    AdaptiveCardParseResult::AdaptiveCardParseResult(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard const& card) :
        AdaptiveCard{card}, Errors{winrt::single_threaded_vector<WinUI3::AdaptiveError>()}, Warnings{winrt::single_threaded_vector <WinUI3::AdaptiveWarning>()}
    {
    }
}
