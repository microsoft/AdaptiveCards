// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFontTypeDefinition.h"
#include "AdaptiveFontTypesDefinition.h"
#include "AdaptiveFontTypesDefinition.g.cpp"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveFontTypesDefinition::AdaptiveFontTypesDefinition(::AdaptiveCards::FontTypesDefinition const& typesDefinition) :
        Default{winrt::make<implementation::AdaptiveFontTypeDefinition>(typesDefinition.defaultFontType)},
        Monospace{winrt::make<implementation::AdaptiveFontTypeDefinition>(typesDefinition.monospaceFontType)}
    {
    }
}
