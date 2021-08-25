// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFontTypeDefinition.h"
#include "AdaptiveFontTypeDefinition.g.cpp"
#include "AdaptiveFontWeightsConfig.h"
#include "AdaptiveFontSizesConfig.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveFontTypeDefinition::AdaptiveFontTypeDefinition(::AdaptiveCards::FontTypeDefinition const& typeDefinition) :
        FontWeights{winrt::make<implementation::AdaptiveFontWeightsConfig>(typeDefinition.fontWeights)},
        FontSizes{winrt::make<implementation::AdaptiveFontSizesConfig>(typeDefinition.fontSizes)}
    {
    }
}
