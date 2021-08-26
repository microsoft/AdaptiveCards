// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveContainerStylesDefinition.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveContainerStylesDefinition : AdaptiveContainerStylesDefinitionT < AdaptiveContainerStylesDefinition>
    {
        AdaptiveContainerStylesDefinition(::AdaptiveCards::ContainerStylesDefinition const& stylesDefinition = {});

        property<WinUI3::AdaptiveContainerStyleDefinition> Default;
        property<WinUI3::AdaptiveContainerStyleDefinition> Emphasis;
        property<WinUI3::AdaptiveContainerStyleDefinition> Good;
        property<WinUI3::AdaptiveContainerStyleDefinition> Attention;
        property<WinUI3::AdaptiveContainerStyleDefinition> Warning;
        property<WinUI3::AdaptiveContainerStyleDefinition> Accent;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveContainerStylesDefinition
        : AdaptiveContainerStylesDefinitionT<AdaptiveContainerStylesDefinition, implementation::AdaptiveContainerStylesDefinition>
    {
    };
}
