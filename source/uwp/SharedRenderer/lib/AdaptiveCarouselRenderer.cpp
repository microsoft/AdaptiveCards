#include "pch.h"
#include "AdaptiveCarouselRenderer.h"
#include "AdaptiveCarouselRenderer.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::Microsoft::UI::Xaml::UIElement AdaptiveCarouselRenderer::Render(
        winrt::AdaptiveCards::ObjectModel::Xaml_Rendering::IAdaptiveCardElement const& element,
        winrt::AdaptiveCards::Rendering::Xaml_Rendering::AdaptiveRenderContext const& context,
        winrt::AdaptiveCards::Rendering::Xaml_Rendering::AdaptiveRenderArgs const& renderArgs)
    {
        FlipView carouselUI{};
        auto carousel = element.as<winrt::IAdaptiveCarousel>();

        winrt::AdaptiveFeatureRegistration featureRegistration = context.FeatureRegistration();
        boolean ancestorHasFallback = renderArgs.AncestorHasFallback();

        for (auto page : carousel.Pages())
        {
            auto [carouselPageUI, carouselPage] =
                ::AdaptiveCards::Rendering::Xaml_Rendering::XamlBuilder::RenderAsUIElement(
                    page,
                    context,
                    renderArgs,
                    featureRegistration,
                    ancestorHasFallback);
			carouselUI.Items().Append(carouselPageUI);
        }

        return carouselUI;
    }
}
