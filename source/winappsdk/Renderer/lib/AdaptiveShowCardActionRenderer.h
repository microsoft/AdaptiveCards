// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveShowCardActionRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveShowCardActionRenderer : AdaptiveShowCardActionRendererT<AdaptiveShowCardActionRenderer>
    {
    public:
        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& action,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);


        static winrt::Windows::UI::Xaml::UIElement
        BuildShowCard(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard const& showCard,
                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs,
                      bool isBottomActionBar);
    };
}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveShowCardActionRenderer
        : AdaptiveShowCardActionRendererT<AdaptiveShowCardActionRenderer, implementation::AdaptiveShowCardActionRenderer>
    {
    };
}
