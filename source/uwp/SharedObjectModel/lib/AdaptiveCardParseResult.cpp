// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardParseResult.h"
#include "AdaptiveCardParseResult.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    AdaptiveCardParseResult::AdaptiveCardParseResult(winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveCard const& card) :
        AdaptiveCard{card}, Errors{winrt::single_threaded_vector<Xaml_OM::AdaptiveError>()}, Warnings{winrt::single_threaded_vector <Xaml_OM::AdaptiveWarning>()}
    {
    }
}
