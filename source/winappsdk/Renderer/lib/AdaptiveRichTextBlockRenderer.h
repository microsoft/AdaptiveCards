// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
#pragma once

#include "AdaptiveRichTextBlockRenderer.g.h"
#include "RichTextBlock.h" // TODO: do we need this import?

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveRichTextBlockRenderer : AdaptiveRichTextBlockRendererT<AdaptiveRichTextBlockRenderer>
    {
        AdaptiveRichTextBlockRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveRichTextBlockRenderer
        : AdaptiveRichTextBlockRendererT<AdaptiveRichTextBlockRenderer, implementation::AdaptiveRichTextBlockRenderer>
    {
    };
}
