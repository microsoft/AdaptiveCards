// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveError.h"
#include "AdaptiveError.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveError::AdaptiveError(winrt::AdaptiveCards::ObjectModel::Uwp::ErrorStatusCode const& statusCode, hstring const& message)
        : Message{message}, StatusCode{statusCode}
    {
    }
}
