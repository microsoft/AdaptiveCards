// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFontTypesDefinition.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveFontTypesDefinition : AdaptiveFontTypesDefinitionT<AdaptiveFontTypesDefinition>
    {
        AdaptiveFontTypesDefinition(::AdaptiveCards::FontTypesDefinition const& fontTypesDefinition = {});

        property<Uwp::AdaptiveFontTypeDefinition> Default;
        property<Uwp::AdaptiveFontTypeDefinition> Monospace;
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveFontTypesDefinition
        : AdaptiveFontTypesDefinitionT<AdaptiveFontTypesDefinition, implementation::AdaptiveFontTypesDefinition>
    {
    };
}
