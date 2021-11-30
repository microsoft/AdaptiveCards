// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveImageSetRenderer.g.h"
#include "ImageSet.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveImageSetRenderer : AdaptiveImageSetRendererT<AdaptiveImageSetRenderer>
    {
    public:
        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveImageSetRenderer : AdaptiveImageSetRendererT<AdaptiveImageSetRenderer, implementation::AdaptiveImageSetRenderer>
    {
    };
}
