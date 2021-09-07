// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardParseResult.h"
#include "AdaptiveCardParseResult.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveCardParseResult::AdaptiveCardParseResult(winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCard const& card) :
        AdaptiveCard{card}, Errors{winrt::single_threaded_vector<Uwp::AdaptiveError>()}, Warnings{winrt::single_threaded_vector <Uwp::AdaptiveWarning>()}
    {
    }
}
