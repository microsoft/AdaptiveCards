// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TextInput.h"
#include "AdaptiveTextInputRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveTextInputRenderer : AdaptiveTextInputRendererT<AdaptiveTextInputRenderer>
    {
        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement element,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext renderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs renderArgs);
        //{
        //    winrt::Windows::UI::Xaml::Controls::TextBox textBox{};
        //    return textBox;
        //}

        winrt::Windows::UI::Xaml::UIElement
        HandleLayoutAndValidation(winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveTextInput adaptiveTextInput,
                                  winrt::Windows::UI::Xaml::Controls::TextBox textBox,
                                  winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext renderContext,
                                  winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs renderArgs);
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveTextInputRenderer : AdaptiveTextInputRendererT<AdaptiveTextInputRenderer, implementation::AdaptiveTextInputRenderer>
    {
    };
}
