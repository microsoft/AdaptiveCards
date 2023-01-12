#pragma once
#include "AdaptiveCardParseResult.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct AdaptiveCardParseResult : AdaptiveCardParseResultT<AdaptiveCardParseResult>
    {
        AdaptiveCardParseResult() : AdaptiveCardParseResult(nullptr) {}
        AdaptiveCardParseResult(winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveCard const& card);

        property<Xaml_OM::AdaptiveCard> AdaptiveCard{nullptr};
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveError>> Errors;
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveWarning>> Warnings;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveCardParseResult : AdaptiveCardParseResultT<AdaptiveCardParseResult, implementation::AdaptiveCardParseResult>
    {
    };
}
