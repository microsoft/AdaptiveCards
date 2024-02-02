// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveCarouselRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveCarouselRenderer : AdaptiveCarouselRendererT<AdaptiveCarouselRenderer>
    {
        AdaptiveCarouselRenderer() = default;
        AdaptiveCarouselRenderer(winrt::com_ptr<::AdaptiveCards::Rendering::Xaml_Rendering::XamlBuilder> xamlBuilder) :
            m_xamlBuilder(xamlBuilder){};

        winrt::UIElement Render(
            winrt::AdaptiveCards::ObjectModel::Xaml_Rendering::IAdaptiveCardElement const& element,
            winrt::AdaptiveCards::Rendering::Xaml_Rendering::AdaptiveRenderContext const& context,
            winrt::AdaptiveCards::Rendering::Xaml_Rendering::AdaptiveRenderArgs const& renderArgs);

        winrt::com_ptr<::AdaptiveCards::Rendering::Xaml_Rendering::XamlBuilder> GetXamlBuilder() { return m_xamlBuilder; }

    private:
        winrt::com_ptr<::AdaptiveCards::Rendering::Xaml_Rendering::XamlBuilder> m_xamlBuilder;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveCarouselRenderer : AdaptiveCarouselRendererT<AdaptiveCarouselRenderer, implementation::AdaptiveCarouselRenderer>
    {
    };
}
