// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveToggleInputRenderer.g.h"

// TODO: do we need this includ here?
#include "ToggleInput.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveToggleInputRenderer : AdaptiveToggleInputRendererT<AdaptiveToggleInputRenderer>
    {
        AdaptiveToggleInputRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveToggleInputRenderer
        : AdaptiveToggleInputRendererT<AdaptiveToggleInputRenderer, implementation::AdaptiveToggleInputRenderer>
    {
    };
}
