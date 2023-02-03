// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveContainerStylesDefinition.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveContainerStylesDefinition : AdaptiveContainerStylesDefinitionT<AdaptiveContainerStylesDefinition>
    {
        AdaptiveContainerStylesDefinition(::AdaptiveCards::ContainerStylesDefinition const& stylesDefinition = {});

        property<winrt::AdaptiveContainerStyleDefinition> Default;
        property<winrt::AdaptiveContainerStyleDefinition> Emphasis;
        property<winrt::AdaptiveContainerStyleDefinition> Good;
        property<winrt::AdaptiveContainerStyleDefinition> Attention;
        property<winrt::AdaptiveContainerStyleDefinition> Warning;
        property<winrt::AdaptiveContainerStyleDefinition> Accent;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveContainerStylesDefinition
        : AdaptiveContainerStylesDefinitionT<AdaptiveContainerStylesDefinition, implementation::AdaptiveContainerStylesDefinition>
    {
    };
}
