// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveToggleInputRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveToggleInputRenderer : AdaptiveToggleInputRendererT<AdaptiveToggleInputRenderer>
    {
        AdaptiveToggleInputRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs);
    };
}

 namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveToggleInputRenderer
        : AdaptiveToggleInputRendererT<AdaptiveToggleInputRenderer, implementation::AdaptiveToggleInputRenderer>
    {
    };
}
