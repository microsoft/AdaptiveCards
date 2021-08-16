// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFactSetConfig.h"
#include "AdaptiveFactSetConfig.g.cpp"
#include "AdaptiveFactSetTextConfig.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveFactSetConfig::AdaptiveFactSetConfig(::AdaptiveCards::FactSetConfig factSetConfig) :
        Title{winrt::make<implementation::AdaptiveFactSetTextConfig>(factSetConfig.title)},
        Value{winrt::make<implementation::AdaptiveFactSetTextConfig>(factSetConfig.value)},
        Spacing{factSetConfig.spacing}
    {
    }
}
