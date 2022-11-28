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

        winrt::xaml::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                                   winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

    private:
        winrt::xaml_automation::Peers::AutomationHeadingLevel GetHeadingLevelFromContext(winrt::render_xaml::AdaptiveRenderContext const& renderContext);
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveTextBlockRenderer : AdaptiveTextBlockRendererT<AdaptiveTextBlockRenderer, implementation::AdaptiveTextBlockRenderer>
    {
    };
}
