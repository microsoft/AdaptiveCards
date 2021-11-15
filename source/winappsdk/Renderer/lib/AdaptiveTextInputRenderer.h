// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTextInputRenderer.g.h"

#include "TextInput.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveTextInputRenderer : AdaptiveTextInputRendererT<AdaptiveTextInputRenderer>
    {
    public:
        AdaptiveTextInputRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

    private:
        winrt::Windows::UI::Xaml::UIElement AdaptiveTextInputRenderer::RenderTextBox(
            winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextInput const& adaptiveTextInput,
            winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
            winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

        winrt::Windows::UI::Xaml::UIElement AdaptiveTextInputRenderer::RenderPasswordBox(
            winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextInput const& adaptiveTextInput,
            winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
            winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

        std::tuple<rtxaml::UIElement, rtxaml::Controls::Border>
        HandleLayoutAndValidation(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextInput const& adaptiveTextInput,
                                  winrt::Windows::UI::Xaml::UIElement const& textBox,
                                  winrt::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext const& renderContext,
                                  winrt::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveTextInputRenderer : AdaptiveTextInputRendererT<AdaptiveTextInputRenderer, implementation::AdaptiveTextInputRenderer>
    {
    };
}
