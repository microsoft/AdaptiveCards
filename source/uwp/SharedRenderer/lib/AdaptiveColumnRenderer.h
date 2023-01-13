// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Column.h"
#include "AdaptiveColumnRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveColumnRenderer : AdaptiveColumnRendererT<AdaptiveColumnRenderer>
    {
        AdaptiveColumnRenderer() = default;
        winrt::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveRenderArgs const& renderArgs);
    };

}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveColumnRenderer : AdaptiveColumnRendererT<AdaptiveColumnRenderer, implementation::AdaptiveColumnRenderer>
    {
    };
}
