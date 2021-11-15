// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveToggleVisibilityActionRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveToggleVisibilityActionRenderer : AdaptiveToggleVisibilityActionRendererT<AdaptiveToggleVisibilityActionRenderer>
    {
        AdaptiveToggleVisibilityActionRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& actionElement,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveToggleVisibilityActionRenderer
        : AdaptiveToggleVisibilityActionRendererT<AdaptiveToggleVisibilityActionRenderer, implementation::AdaptiveToggleVisibilityActionRenderer>
    {
    };
}
