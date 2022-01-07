// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveExecuteActionRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveExecuteActionRenderer : AdaptiveExecuteActionRendererT<AdaptiveExecuteActionRenderer>
    {
        AdaptiveExecuteActionRenderer() = default;

        Windows::UI::Xaml::UIElement Render(winrt::IAdaptiveActionElement const& action,
                                            winrt::AdaptiveRenderContext const& renderContext,
                                            winrt::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveExecuteActionRenderer
        : AdaptiveExecuteActionRendererT<AdaptiveExecuteActionRenderer, implementation::AdaptiveExecuteActionRenderer>
    {
    };
}
