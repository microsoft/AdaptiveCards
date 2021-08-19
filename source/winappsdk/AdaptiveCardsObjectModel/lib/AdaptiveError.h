#pragma once
#include "AdaptiveError.g.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct AdaptiveError : AdaptiveErrorT<AdaptiveError>
    {
        AdaptiveError(winrt::AdaptiveCards::ObjectModel::WinUI3::ErrorStatusCode const& statusCode, hstring const& message);

        property<hstring> Message;
        property<winrt::AdaptiveCards::ObjectModel::WinUI3::ErrorStatusCode> StatusCode;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::WinUI3::factory_implementation
{
    struct AdaptiveError : AdaptiveErrorT<AdaptiveError, implementation::AdaptiveError>
    {
    };
}
