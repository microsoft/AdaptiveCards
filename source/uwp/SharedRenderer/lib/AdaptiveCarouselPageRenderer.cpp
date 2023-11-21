#include "pch.h"

#include "ActionHelpers.h"
#include "AdaptiveCarouselPageRenderer.h"
#include "AdaptiveCarouselPageRenderer.g.cpp"
#include "AdaptiveRenderArgs.h"

#include "WholeItemsPanel.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::Microsoft::UI::Xaml::UIElement AdaptiveCarouselPageRenderer::Render(
        winrt::IAdaptiveCardElement const& cardElement,
        winrt::AdaptiveRenderContext const& renderContext,
        winrt::AdaptiveRenderArgs const& renderArgs)
    {
        // Carousel Page is just a Container
        // Added the renderer here anyway for future bifurcation
		auto containerRenderer = renderContext.ElementRenderers().Get(L"Container");
        return containerRenderer.Render(cardElement, renderContext, renderArgs);
    }
}
