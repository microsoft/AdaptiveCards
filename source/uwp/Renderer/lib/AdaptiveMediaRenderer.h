// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveMediaRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveMediaRenderer : AdaptiveMediaRendererT<AdaptiveMediaRenderer>
    {
    public:
        AdaptiveMediaRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveMediaRenderer : AdaptiveMediaRendererT<AdaptiveMediaRenderer, implementation::AdaptiveMediaRenderer>
    {
    };
}
