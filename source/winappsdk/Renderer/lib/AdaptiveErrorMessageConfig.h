// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveErrorMessageConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveErrorMessageConfig : AdaptiveErrorMessageConfigT<AdaptiveErrorMessageConfig>
    {
        AdaptiveErrorMessageConfig(::AdaptiveCards::ErrorMessageConfig errorMessageConfig = {});

        property<ObjectModel::WinUI3::TextSize> Size;
        property<ObjectModel::WinUI3::Spacing> Spacing;
        property<ObjectModel::WinUI3::TextWeight> Weight;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveErrorMessageConfig : AdaptiveErrorMessageConfigT<AdaptiveErrorMessageConfig, implementation::AdaptiveErrorMessageConfig>
    {
    };
}
