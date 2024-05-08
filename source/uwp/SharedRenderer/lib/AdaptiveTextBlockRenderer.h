// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTextBlockRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveTextBlockRenderer : AdaptiveTextBlockRendererT<AdaptiveTextBlockRenderer>
    {
    public:
        AdaptiveTextBlockRenderer() = default;

        winrt::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveRenderArgs const& renderArgs);

    private:
        winrt::AutomationHeadingLevel GetHeadingLevelFromContext(winrt::AdaptiveRenderContext const& renderContext);
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveTextBlockRenderer : AdaptiveTextBlockRendererT<AdaptiveTextBlockRenderer, implementation::AdaptiveTextBlockRenderer>
    {
    };
}
