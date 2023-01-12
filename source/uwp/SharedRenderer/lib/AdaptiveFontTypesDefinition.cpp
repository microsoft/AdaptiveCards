// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFontTypeDefinition.h"
#include "AdaptiveFontTypesDefinition.h"
#include "AdaptiveFontTypesDefinition.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveFontTypesDefinition::AdaptiveFontTypesDefinition(::AdaptiveCards::FontTypesDefinition const& typesDefinition) :
        Default{winrt::make<implementation::AdaptiveFontTypeDefinition>(typesDefinition.defaultFontType)},
        Monospace{winrt::make<implementation::AdaptiveFontTypeDefinition>(typesDefinition.monospaceFontType)}
    {
    }
}
