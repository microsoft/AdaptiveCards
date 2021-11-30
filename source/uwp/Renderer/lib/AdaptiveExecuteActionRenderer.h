// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveExecuteActionRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveExecuteActionRenderer : AdaptiveExecuteActionRendererT<AdaptiveExecuteActionRenderer>
    {
        AdaptiveExecuteActionRenderer() = default;

        Windows::UI::Xaml::UIElement Render(AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& action,
                                            AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                            AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveExecuteActionRenderer
        : AdaptiveExecuteActionRendererT<AdaptiveExecuteActionRenderer, implementation::AdaptiveExecuteActionRenderer>
    {
    };
}
