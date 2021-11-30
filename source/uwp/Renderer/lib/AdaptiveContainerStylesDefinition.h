// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveContainerStylesDefinition.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveContainerStylesDefinition : AdaptiveContainerStylesDefinitionT < AdaptiveContainerStylesDefinition>
    {
        AdaptiveContainerStylesDefinition(::AdaptiveCards::ContainerStylesDefinition const& stylesDefinition = {});

        property<Uwp::AdaptiveContainerStyleDefinition> Default;
        property<Uwp::AdaptiveContainerStyleDefinition> Emphasis;
        property<Uwp::AdaptiveContainerStyleDefinition> Good;
        property<Uwp::AdaptiveContainerStyleDefinition> Attention;
        property<Uwp::AdaptiveContainerStyleDefinition> Warning;
        property<Uwp::AdaptiveContainerStyleDefinition> Accent;
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveContainerStylesDefinition
        : AdaptiveContainerStylesDefinitionT<AdaptiveContainerStylesDefinition, implementation::AdaptiveContainerStylesDefinition>
    {
    };
}
