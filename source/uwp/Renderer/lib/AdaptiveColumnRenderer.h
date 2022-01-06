// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Column.h"
#include "AdaptiveColumnRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveColumnRenderer : AdaptiveColumnRendererT<AdaptiveColumnRenderer>
    {
        AdaptiveColumnRenderer() = default;
        winrt::Windows::UI::Xaml::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);
    };

}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveColumnRenderer : AdaptiveColumnRendererT<AdaptiveColumnRenderer, implementation::AdaptiveColumnRenderer>
    {
    };
}
