// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveWarning.h"
#include "AdaptiveWarning.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    AdaptiveWarning::AdaptiveWarning(winrt::AdaptiveCards::ObjectModel::Xaml_OM::WarningStatusCode const& statusCode, hstring const& message) :
        StatusCode{statusCode}, Message{message}
    {
    }
}
