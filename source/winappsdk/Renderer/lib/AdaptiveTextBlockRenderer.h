// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTextBlockRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveTextBlockRenderer : AdaptiveTextBlockRendererT<AdaptiveTextBlockRenderer>
    {
    public:
        AdaptiveTextBlockRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

    private:
        winrt::Windows::UI::Xaml::Automation::Peers::AutomationHeadingLevel
        GetHeadingLevelFromContext(winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveTextBlockRenderer : AdaptiveTextBlockRendererT<AdaptiveTextBlockRenderer, implementation::AdaptiveTextBlockRenderer>
    {
    };
}
