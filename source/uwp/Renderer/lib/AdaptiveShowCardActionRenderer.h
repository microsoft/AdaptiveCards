// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveShowCardActionRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveShowCardActionRenderer : AdaptiveShowCardActionRendererT<AdaptiveShowCardActionRenderer>
    {
    public:
        winrt::UIElement Render(winrt::IAdaptiveActionElement const& action,
                                                   winrt::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveRenderArgs const& renderArgs);

        static winrt::UIElement BuildShowCard(winrt::AdaptiveCard const& showCard,
                                                                 winrt::AdaptiveRenderContext const& renderContext,
                                                                 winrt::AdaptiveRenderArgs const& renderArgs,
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
