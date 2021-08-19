#pragma once
#include "AdaptiveCardParseResult.g.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct AdaptiveCardParseResult : AdaptiveCardParseResultT<AdaptiveCardParseResult>
    {
        AdaptiveCardParseResult() : AdaptiveCardParseResult(nullptr) {}
        AdaptiveCardParseResult(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard const& card);

        property<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard> AdaptiveCard;
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveError>> Errors;
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning>> Warnings;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::WinUI3::factory_implementation
{
    struct AdaptiveCardParseResult : AdaptiveCardParseResultT<AdaptiveCardParseResult, implementation::AdaptiveCardParseResult>
    {
    };
}
