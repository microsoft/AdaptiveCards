// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveErrorMessageConfig.h"
#include "AdaptiveErrorMessageConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveErrorMessageConfig::AdaptiveErrorMessageConfig(::AdaptiveCards::ErrorMessageConfig errorMessageConfig)
    {
        Size = static_cast<ObjectModel::WinUI3::TextSize>(errorMessageConfig.size);
        Spacing = static_cast<ObjectModel::WinUI3::Spacing>(errorMessageConfig.spacing);
        Weight = static_cast<ObjectModel::WinUI3::TextWeight>(errorMessageConfig.weight);
    }
}
