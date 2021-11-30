// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveShowCardActionRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveShowCardActionRenderer : AdaptiveShowCardActionRendererT<AdaptiveShowCardActionRenderer>
    {
    public:
        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& action,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

        static winrt::Windows::UI::Xaml::UIElement
        BuildShowCard(winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCard const& showCard,
                      winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                      winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs,
                      bool isBottomActionBar);
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveShowCardActionRenderer
        : AdaptiveShowCardActionRendererT<AdaptiveShowCardActionRenderer, implementation::AdaptiveShowCardActionRenderer>
    {
    };
}
