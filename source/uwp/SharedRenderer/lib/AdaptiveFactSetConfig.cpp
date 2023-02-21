// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFactSetConfig.h"
#include "AdaptiveFactSetConfig.g.cpp"
#include "AdaptiveFactSetTextConfig.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveFactSetConfig::AdaptiveFactSetConfig(::AdaptiveCards::FactSetConfig const& factSetConfig) :
        Title{winrt::make<implementation::AdaptiveFactSetTextConfig>(factSetConfig.title)},
        Value{winrt::make<implementation::AdaptiveFactSetTextConfig>(factSetConfig.value)}, Spacing{factSetConfig.spacing}
    {
    }
}
