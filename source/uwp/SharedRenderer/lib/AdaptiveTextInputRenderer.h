// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTextInputRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveTextInputRenderer : AdaptiveTextInputRendererT<AdaptiveTextInputRenderer>
    {
    public:
        AdaptiveTextInputRenderer() = default;

        winrt::xaml::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                      winrt::AdaptiveRenderContext const& renderContext,
                                      winrt::AdaptiveRenderArgs const& renderArgs);

    private:
        winrt::xaml::UIElement AdaptiveTextInputRenderer::RenderTextBox(winrt::AdaptiveTextInput const& adaptiveTextInput,
                                                                        winrt::AdaptiveRenderContext const& renderContext,
                                                                        winrt::AdaptiveRenderArgs const& renderArgs);

        winrt::xaml::UIElement AdaptiveTextInputRenderer::RenderPasswordBox(winrt::AdaptiveTextInput const& adaptiveTextInput,
                                                                            winrt::AdaptiveRenderContext const& renderContext,
                                                                            winrt::AdaptiveRenderArgs const& renderArgs);

        std::tuple<winrt::xaml::UIElement, winrt::xaml_controls::Border>
        HandleLayoutAndValidation(winrt::AdaptiveTextInput const& adaptiveTextInput,
                                  winrt::xaml::UIElement const& textBox,
                                  winrt::AdaptiveRenderContext const& renderContext,
                                  winrt::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveTextInputRenderer : AdaptiveTextInputRendererT<AdaptiveTextInputRenderer, implementation::AdaptiveTextInputRenderer>
    {
    };
}
