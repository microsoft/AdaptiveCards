// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTableConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveTableConfig : AdaptiveTableConfigT<AdaptiveTableConfig>
    {
        AdaptiveTableConfig(::AdaptiveCards::TableConfig const& tableConfig = {});

        property<uint32_t> CellSpacing;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveTableConfig : AdaptiveTableConfigT<AdaptiveTableConfig, implementation::AdaptiveTableConfig>
    {
    };
}
