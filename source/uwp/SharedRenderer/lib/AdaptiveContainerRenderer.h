// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveContainerRenderer.g.h"
#include "Container.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveContainerRenderer : AdaptiveContainerRendererT<AdaptiveContainerRenderer>
    {
        AdaptiveContainerRenderer() = default;

        winrt::UIElement Render(winrt::IAdaptiveCardElement const& element,
                                winrt::AdaptiveRenderContext const& context,
                                winrt::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveContainerRenderer : AdaptiveContainerRendererT<AdaptiveContainerRenderer, implementation::AdaptiveContainerRenderer>
    {
    };
}
