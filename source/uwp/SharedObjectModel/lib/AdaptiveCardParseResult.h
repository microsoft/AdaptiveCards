#pragma once
#include "AdaptiveCardParseResult.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct AdaptiveCardParseResult : AdaptiveCardParseResultT<AdaptiveCardParseResult>
    {
        AdaptiveCardParseResult() : AdaptiveCardParseResult(nullptr) {}
        AdaptiveCardParseResult(winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCard const& card);

        property<Uwp::AdaptiveCard> AdaptiveCard{nullptr};
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveError>> Errors;
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning>> Warnings;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveCardParseResult : AdaptiveCardParseResultT<AdaptiveCardParseResult, implementation::AdaptiveCardParseResult>
    {
    };
}
