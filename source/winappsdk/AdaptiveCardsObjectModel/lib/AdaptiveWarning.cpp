// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveWarning.h"
#include "AdaptiveWarning.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    AdaptiveWarning::AdaptiveWarning(winrt::AdaptiveCards::ObjectModel::WinUI3::WarningStatusCode const& statusCode, hstring const& message) :
        StatusCode{statusCode}, Message{message}
    {
    }
}
