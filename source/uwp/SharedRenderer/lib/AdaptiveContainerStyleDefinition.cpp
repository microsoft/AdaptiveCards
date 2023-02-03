// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveContainerStyleDefinition.h"
#include "AdaptiveContainerStyleDefinition.g.cpp"
#include "AdaptiveColorsConfig.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveContainerStyleDefinition::AdaptiveContainerStyleDefinition(::AdaptiveCards::ContainerStyleDefinition styleDefinition) :
        ForegroundColors{winrt::make<implementation::AdaptiveColorsConfig>(styleDefinition.foregroundColors)},
        BackgroundColor{GetColorFromString(styleDefinition.backgroundColor)}, BorderColor{GetColorFromString(
                                                                                  styleDefinition.borderColor)}
    {
    }
}
