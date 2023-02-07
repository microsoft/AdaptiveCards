// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFactSetTextConfig.h"
#include "AdaptiveFactSetTextConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveFactSetTextConfig::AdaptiveFactSetTextConfig(::AdaptiveCards::FactSetTextConfig const& textConfig) :
        AdaptiveTextStyleConfigBase(textConfig)
    {
        Wrap = textConfig.wrap;
        MaxWidth = textConfig.maxWidth;
    }
}
