#pragma once
#include "AdaptiveWarning.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct AdaptiveWarning : AdaptiveWarningT<AdaptiveWarning>
    {
        AdaptiveWarning(winrt::AdaptiveCards::ObjectModel::Xaml_OM::WarningStatusCode const& statusCode, hstring const& message);
        property<Xaml_OM::WarningStatusCode> StatusCode;
        property<hstring> Message;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveWarning : AdaptiveWarningT<AdaptiveWarning, implementation::AdaptiveWarning>
    {
    };
}
