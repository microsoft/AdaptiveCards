// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextStyleConfig.h"
#include "AdaptiveTextStylesConfig.h"
#include "AdaptiveTextStylesConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveTextStylesConfig::AdaptiveTextStylesConfig(::AdaptiveCards::TextStylesConfig const& textStylesConfig) :
        Heading{winrt::make<implementation::AdaptiveTextStyleConfig>(textStylesConfig.heading)},
        ColumnHeader{winrt::make<implementation::AdaptiveTextStyleConfig>(textStylesConfig.columnHeader)}
    {
    }
}
