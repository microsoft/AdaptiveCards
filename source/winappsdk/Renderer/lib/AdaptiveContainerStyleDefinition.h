// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveContainerStyleDefinition.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveContainerStyleDefinition : AdaptiveContainerStyleDefinitionT<AdaptiveContainerStyleDefinition>
    {
        AdaptiveContainerStyleDefinition(::AdaptiveCards::ContainerStyleDefinition styleDefinition = {});

        property<winrt::Windows::UI::Color> BackgroundColor;
        property<winrt::Windows::UI::Color> BorderColor;
        property<winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveColorsConfig> ForegroundColors;
        property<winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveColorsConfig> HighlightColors;
    };
}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveContainerStyleDefinition
        : AdaptiveContainerStyleDefinitionT<AdaptiveContainerStyleDefinition, implementation::AdaptiveContainerStyleDefinition>
    {
    };
}
