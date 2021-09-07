// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ActionSet.h"
#include "AdaptiveActionSetRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveActionSetRenderer : AdaptiveActionSetRendererT<AdaptiveActionSetRenderer>
    {
        AdaptiveActionSetRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
                                                   WinUI3::AdaptiveRenderContext const& renderContext,
                                                   WinUI3::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveActionSetRenderer : AdaptiveActionSetRendererT<AdaptiveActionSetRenderer, implementation::AdaptiveActionSetRenderer>
    {
    };
}
