// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveError.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct AdaptiveError : AdaptiveErrorT<AdaptiveError>
    {
        AdaptiveError(winrt::AdaptiveCards::ObjectModel::Xaml_OM::ErrorStatusCode const& statusCode, hstring const& message);

        property<hstring> Message;
        property<Xaml_OM::ErrorStatusCode> StatusCode;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveError : AdaptiveErrorT<AdaptiveError, implementation::AdaptiveError>
    {
    };
}
