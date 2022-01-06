// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveOpenUrlActionRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveOpenUrlActionRenderer : AdaptiveOpenUrlActionRendererT<AdaptiveOpenUrlActionRenderer>
    {
        AdaptiveOpenUrlActionRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::IAdaptiveActionElement const& action,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveOpenUrlActionRenderer
        : AdaptiveOpenUrlActionRendererT<AdaptiveOpenUrlActionRenderer, implementation::AdaptiveOpenUrlActionRenderer>
    {
    };
}
