// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
#pragma once

#include "AdaptiveRichTextBlockRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveRichTextBlockRenderer : AdaptiveRichTextBlockRendererT<AdaptiveRichTextBlockRenderer>
    {
        AdaptiveRichTextBlockRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveRichTextBlockRenderer
        : AdaptiveRichTextBlockRendererT<AdaptiveRichTextBlockRenderer, implementation::AdaptiveRichTextBlockRenderer>
    {
    };
}
