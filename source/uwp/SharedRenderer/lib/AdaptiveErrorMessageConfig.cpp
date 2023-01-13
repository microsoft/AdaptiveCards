// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveErrorMessageConfig.h"
#include "AdaptiveErrorMessageConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveErrorMessageConfig::AdaptiveErrorMessageConfig(::AdaptiveCards::ErrorMessageConfig errorMessageConfig)
    {
        Size = static_cast<winrt::TextSize>(errorMessageConfig.size);
        Spacing = static_cast<winrt::Spacing>(errorMessageConfig.spacing);
        Weight = static_cast<winrt::TextWeight>(errorMessageConfig.weight);
    }
}
