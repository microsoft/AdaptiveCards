// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveContainerStyleDefinition.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveContainerStyleDefinition : AdaptiveContainerStyleDefinitionT<AdaptiveContainerStyleDefinition>
    {
        AdaptiveContainerStyleDefinition(::AdaptiveCards::ContainerStyleDefinition styleDefinition = {});

        property<winrt::Windows::UI::Color> BackgroundColor;
        property<winrt::Windows::UI::Color> BorderColor;
        property<winrt::render_xaml::AdaptiveColorsConfig> ForegroundColors;
        property<winrt::render_xaml::AdaptiveColorsConfig> HighlightColors;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveContainerStyleDefinition
        : AdaptiveContainerStyleDefinitionT<AdaptiveContainerStyleDefinition, implementation::AdaptiveContainerStyleDefinition>
    {
    };
}
