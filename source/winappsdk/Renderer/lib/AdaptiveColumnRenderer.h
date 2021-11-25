// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Column.h"
#include "AdaptiveColumnRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveColumnRenderer : AdaptiveColumnRendererT<AdaptiveColumnRenderer>
    {
        AdaptiveColumnRenderer() = default;
        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);
    };

}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveColumnRenderer : AdaptiveColumnRendererT<AdaptiveColumnRenderer, implementation::AdaptiveColumnRenderer>
    {
    };
}
