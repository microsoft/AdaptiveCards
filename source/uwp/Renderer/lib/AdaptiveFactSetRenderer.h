// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFactSetRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveFactSetRenderer : AdaptiveFactSetRendererT<AdaptiveFactSetRenderer>
    {
        AdaptiveFactSetRenderer() = default;

        Windows::UI::Xaml::UIElement Render(AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement const& cardElement,
                                            AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                            AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveFactSetRenderer : AdaptiveFactSetRendererT<AdaptiveFactSetRenderer, implementation::AdaptiveFactSetRenderer>
    {
    };
}
