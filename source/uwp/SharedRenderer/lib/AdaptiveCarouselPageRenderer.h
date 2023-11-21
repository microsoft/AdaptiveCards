#pragma once
#include "AdaptiveCarouselPageRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveCarouselPageRenderer : AdaptiveCarouselPageRendererT<AdaptiveCarouselPageRenderer>
    {
        AdaptiveCarouselPageRenderer() = default;

        winrt::Microsoft::UI::Xaml::UIElement Render(
            winrt::AdaptiveCards::ObjectModel::Xaml_Rendering::IAdaptiveCardElement const& element,
            winrt::AdaptiveCards::Rendering::Xaml_Rendering::AdaptiveRenderContext const& context,
            winrt::AdaptiveCards::Rendering::Xaml_Rendering::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveCarouselPageRenderer : AdaptiveCarouselPageRendererT<AdaptiveCarouselPageRenderer, implementation::AdaptiveCarouselPageRenderer>
    {
    };
}
