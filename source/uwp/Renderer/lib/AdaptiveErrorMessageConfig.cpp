// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveErrorMessageConfig.h"
#include "AdaptiveErrorMessageConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    AdaptiveErrorMessageConfig::AdaptiveErrorMessageConfig(::AdaptiveCards::ErrorMessageConfig errorMessageConfig)
    {
        Size = static_cast<ObjectModel::Uwp::TextSize>(errorMessageConfig.size);
        Spacing = static_cast<ObjectModel::Uwp::Spacing>(errorMessageConfig.spacing);
        Weight = static_cast<ObjectModel::Uwp::TextWeight>(errorMessageConfig.weight);
    }
}
