// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveContainerStyleDefinition.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveContainerStyleDefinition : AdaptiveContainerStyleDefinitionT<AdaptiveContainerStyleDefinition>
    {
        AdaptiveContainerStyleDefinition(::AdaptiveCards::ContainerStyleDefinition styleDefinition = {});

        property<winrt::Windows::UI::Color> BackgroundColor;
        property<winrt::Windows::UI::Color> BorderColor;
        property<winrt::AdaptiveCards::Rendering::Uwp::AdaptiveColorsConfig> ForegroundColors;
        property<winrt::AdaptiveCards::Rendering::Uwp::AdaptiveColorsConfig> HighlightColors;
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveContainerStyleDefinition
        : AdaptiveContainerStyleDefinitionT<AdaptiveContainerStyleDefinition, implementation::AdaptiveContainerStyleDefinition>
    {
    };
}
