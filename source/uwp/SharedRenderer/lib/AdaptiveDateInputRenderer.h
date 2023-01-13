// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveDateInputRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveDateInputRenderer : AdaptiveDateInputRendererT<AdaptiveDateInputRenderer>
    {
        AdaptiveDateInputRenderer() = default;

        winrt::UIElement Render(winrt::IAdaptiveCardElement const& element,
                                                   winrt::AdaptiveRenderContext const& context,
                                                   winrt::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveDateInputRenderer : AdaptiveDateInputRendererT<AdaptiveDateInputRenderer, implementation::AdaptiveDateInputRenderer>
    {
    };
}
