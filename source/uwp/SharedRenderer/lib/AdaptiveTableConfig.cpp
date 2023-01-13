// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTableConfig.h"
#include "AdaptiveTableConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveTableConfig::AdaptiveTableConfig(::AdaptiveCards::TableConfig const& tableConfig)
    {
        CellSpacing = tableConfig.cellSpacing;
    }
}
