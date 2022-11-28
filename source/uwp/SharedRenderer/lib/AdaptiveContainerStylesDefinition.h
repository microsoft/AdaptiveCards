// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveContainerStylesDefinition.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveContainerStylesDefinition : AdaptiveContainerStylesDefinitionT<AdaptiveContainerStylesDefinition>
    {
        AdaptiveContainerStylesDefinition(::AdaptiveCards::ContainerStylesDefinition const& stylesDefinition = {});

        property<winrt::render_xaml::AdaptiveContainerStyleDefinition> Default;
        property<winrt::render_xaml::AdaptiveContainerStyleDefinition> Emphasis;
        property<winrt::render_xaml::AdaptiveContainerStyleDefinition> Good;
        property<winrt::render_xaml::AdaptiveContainerStyleDefinition> Attention;
        property<winrt::render_xaml::AdaptiveContainerStyleDefinition> Warning;
        property<winrt::render_xaml::AdaptiveContainerStyleDefinition> Accent;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveContainerStylesDefinition
        : AdaptiveContainerStylesDefinitionT<AdaptiveContainerStylesDefinition, implementation::AdaptiveContainerStylesDefinition>
    {
    };
}
