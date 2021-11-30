// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveDateInputRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveDateInputRenderer : AdaptiveDateInputRendererT<AdaptiveDateInputRenderer>
    {
        AdaptiveDateInputRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement const& element,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& context,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveDateInputRenderer : AdaptiveDateInputRendererT<AdaptiveDateInputRenderer, implementation::AdaptiveDateInputRenderer>
    {
    };
}
