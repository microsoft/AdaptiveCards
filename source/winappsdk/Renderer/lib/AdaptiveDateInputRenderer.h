// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveDateInputRenderer.g.h"
#include "DateInput.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveDateInputRenderer : AdaptiveDateInputRendererT<AdaptiveDateInputRenderer>
    {
        AdaptiveDateInputRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& element,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& context,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveDateInputRenderer : AdaptiveDateInputRendererT<AdaptiveDateInputRenderer, implementation::AdaptiveDateInputRenderer>
    {
    };
}
