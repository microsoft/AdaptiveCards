// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ActionSet.h"
#include "AdaptiveActionSetRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveActionSetRenderer : AdaptiveActionSetRendererT<AdaptiveActionSetRenderer>
    {
        AdaptiveActionSetRenderer() = default;

        winrt::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   Uwp::AdaptiveRenderContext const& renderContext,
                                                   Uwp::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveActionSetRenderer : AdaptiveActionSetRendererT<AdaptiveActionSetRenderer, implementation::AdaptiveActionSetRenderer>
    {
    };
}
