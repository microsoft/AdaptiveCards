// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ColumnSet.h"
#include "AdaptiveColumnSetRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveColumnSetRenderer : AdaptiveColumnSetRendererT<AdaptiveColumnSetRenderer>
    {
    public:
        AdaptiveColumnSetRenderer() = default;

        winrt::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveRenderArgs const& renderArgs);
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveColumnSetRenderer : AdaptiveColumnSetRendererT<AdaptiveColumnSetRenderer, implementation::AdaptiveColumnSetRenderer>
    {
    };
}
