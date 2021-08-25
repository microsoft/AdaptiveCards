// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFontTypeDefinition.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveFontTypeDefinition : AdaptiveFontTypeDefinitionT<AdaptiveFontTypeDefinition>
    {
        AdaptiveFontTypeDefinition(::AdaptiveCards::FontTypeDefinition const& fontTypeDefinition = {});

        property<hstring> FontFamily;
        property<WinUI3::AdaptiveFontWeightsConfig> FontWeights;
        property<WinUI3::AdaptiveFontSizesConfig> FontSizes;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveFontTypeDefinition : AdaptiveFontTypeDefinitionT<AdaptiveFontTypeDefinition, implementation::AdaptiveFontTypeDefinition>
    {
    };
}
