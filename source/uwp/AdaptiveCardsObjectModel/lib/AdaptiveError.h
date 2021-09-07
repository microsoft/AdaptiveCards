#pragma once
#include "AdaptiveError.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct AdaptiveError : AdaptiveErrorT<AdaptiveError>
    {
        AdaptiveError(winrt::AdaptiveCards::ObjectModel::Uwp::ErrorStatusCode const& statusCode, hstring const& message);

        property<hstring> Message;
        property<Uwp::ErrorStatusCode> StatusCode;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveError : AdaptiveErrorT<AdaptiveError, implementation::AdaptiveError>
    {
    };
}
