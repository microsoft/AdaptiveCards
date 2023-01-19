// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveContainerStyleDefinition.h"
#include "AdaptiveContainerStylesDefinition.h"
#include "AdaptiveContainerStylesDefinition.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveContainerStylesDefinition::AdaptiveContainerStylesDefinition(::AdaptiveCards::ContainerStylesDefinition const& stylesDefinition) :
        Default{winrt::make<implementation::AdaptiveContainerStyleDefinition>(stylesDefinition.defaultPalette)},
        Emphasis{winrt::make<implementation::AdaptiveContainerStyleDefinition>(stylesDefinition.emphasisPalette)},
        Good{winrt::make<implementation::AdaptiveContainerStyleDefinition>(stylesDefinition.goodPalette)},
        Attention{winrt::make<implementation::AdaptiveContainerStyleDefinition>(stylesDefinition.attentionPalette)},
        Warning{winrt::make<implementation::AdaptiveContainerStyleDefinition>(stylesDefinition.warningPalette)},
        Accent{winrt::make<implementation::AdaptiveContainerStyleDefinition>(stylesDefinition.accentPalette)}
    {
    }
}
