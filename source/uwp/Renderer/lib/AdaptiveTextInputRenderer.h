// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTextInputRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveTextInputRenderer : AdaptiveTextInputRendererT<AdaptiveTextInputRenderer>
    {
    public:
        AdaptiveTextInputRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

    private:
        winrt::Windows::UI::Xaml::UIElement AdaptiveTextInputRenderer::RenderTextBox(
            winrt::AdaptiveTextInput const& adaptiveTextInput,
            winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
            winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

        winrt::Windows::UI::Xaml::UIElement AdaptiveTextInputRenderer::RenderPasswordBox(
            winrt::AdaptiveTextInput const& adaptiveTextInput,
            winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
            winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

        std::tuple<rtxaml::UIElement, winrt::Border>
        HandleLayoutAndValidation(winrt::AdaptiveTextInput const& adaptiveTextInput,
                                  winrt::Windows::UI::Xaml::UIElement const& textBox,
                                  winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                  winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveTextInputRenderer : AdaptiveTextInputRendererT<AdaptiveTextInputRenderer, implementation::AdaptiveTextInputRenderer>
    {
    };
}
