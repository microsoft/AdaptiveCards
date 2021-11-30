// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTextBlockRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveTextBlockRenderer : AdaptiveTextBlockRendererT<AdaptiveTextBlockRenderer>
    {
    public:
        AdaptiveTextBlockRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

    private:
        winrt::Windows::UI::Xaml::Automation::Peers::AutomationHeadingLevel
        GetHeadingLevelFromContext(winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext);
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveTextBlockRenderer : AdaptiveTextBlockRendererT<AdaptiveTextBlockRenderer, implementation::AdaptiveTextBlockRenderer>
    {
    };
}
