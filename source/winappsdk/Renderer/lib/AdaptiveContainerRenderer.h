// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveContainerRenderer.g.h"
#include "Container.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveContainerRenderer : AdaptiveContainerRendererT<AdaptiveContainerRenderer>
    {
        AdaptiveContainerRenderer() = default;

        Windows::UI::Xaml::UIElement Render(AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& element,
                                            AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& context,
                                            AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveContainerRenderer : AdaptiveContainerRendererT<AdaptiveContainerRenderer, implementation::AdaptiveContainerRenderer>
    {
    };
}
