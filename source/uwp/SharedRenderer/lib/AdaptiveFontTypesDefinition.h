// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFontTypesDefinition.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveFontTypesDefinition : AdaptiveFontTypesDefinitionT<AdaptiveFontTypesDefinition>
    {
        AdaptiveFontTypesDefinition(::AdaptiveCards::FontTypesDefinition const& fontTypesDefinition = {});

        property<winrt::render_xaml::AdaptiveFontTypeDefinition> Default;
        property<winrt::render_xaml::AdaptiveFontTypeDefinition> Monospace;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveFontTypesDefinition
        : AdaptiveFontTypesDefinitionT<AdaptiveFontTypesDefinition, implementation::AdaptiveFontTypesDefinition>
    {
    };
}
