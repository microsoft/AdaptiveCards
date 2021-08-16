// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFontTypesDefinition.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveFontTypesDefinition : AdaptiveFontTypesDefinitionT<AdaptiveFontTypesDefinition>
    {
        AdaptiveFontTypesDefinition(::AdaptiveCards::FontTypesDefinition const& fontTypesDefinition = {});

        property<WinUI3::AdaptiveFontTypeDefinition> Default;
        property<WinUI3::AdaptiveFontTypeDefinition> Monospace;
    };
}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveFontTypesDefinition
        : AdaptiveFontTypesDefinitionT<AdaptiveFontTypesDefinition, implementation::AdaptiveFontTypesDefinition>
    {
    };
}
