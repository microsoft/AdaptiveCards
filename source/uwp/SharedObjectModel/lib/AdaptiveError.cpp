// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveError.h"
#include "AdaptiveError.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    AdaptiveError::AdaptiveError(winrt::AdaptiveCards::ObjectModel::Xaml_OM::ErrorStatusCode const& statusCode, hstring const& message)
        : Message{message}, StatusCode{statusCode}
    {
    }
}
