// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFactRenderer.g.h"

// TODO: Do we need this import here?
#include "FactSet.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveFactRenderer : AdaptiveFactRendererT<AdaptiveFactRenderer>
    {
        AdaptiveFactRenderer() = default;

        Windows::UI::Xaml::UIElement Render(AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
                                            AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                            AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveFactRenderer : AdaptiveFactRendererT<AdaptiveFactRenderer, implementation::AdaptiveFactRenderer>
    {
    };
}
