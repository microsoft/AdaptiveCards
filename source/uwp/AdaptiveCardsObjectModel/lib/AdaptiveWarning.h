#pragma once
#include "AdaptiveWarning.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct AdaptiveWarning : AdaptiveWarningT<AdaptiveWarning>
    {
        AdaptiveWarning(winrt::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode const& statusCode, hstring const& message);
        property<Uwp::WarningStatusCode> StatusCode;
        property<hstring> Message;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveWarning : AdaptiveWarningT<AdaptiveWarning, implementation::AdaptiveWarning>
    {
    };
}
