#pragma once
#include "AdaptiveWarning.g.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct AdaptiveWarning : AdaptiveWarningT<AdaptiveWarning>
    {
        AdaptiveWarning(winrt::AdaptiveCards::ObjectModel::WinUI3::WarningStatusCode const& statusCode, hstring const& message);
        property<WinUI3::WarningStatusCode> StatusCode;
        property<hstring> Message;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::WinUI3::factory_implementation
{
    struct AdaptiveWarning : AdaptiveWarningT<AdaptiveWarning, implementation::AdaptiveWarning>
    {
    };
}
