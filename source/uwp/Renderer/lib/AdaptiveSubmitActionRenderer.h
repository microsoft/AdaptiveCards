// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveSubmitActionRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveSubmitActionRenderer : AdaptiveSubmitActionRendererT<AdaptiveSubmitActionRenderer>
    {
        AdaptiveSubmitActionRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& action,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveSubmitActionRenderer
        : AdaptiveSubmitActionRendererT<AdaptiveSubmitActionRenderer, implementation::AdaptiveSubmitActionRenderer>
    {
    };
}
