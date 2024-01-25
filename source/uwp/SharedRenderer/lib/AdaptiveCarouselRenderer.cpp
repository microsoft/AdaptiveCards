#include "pch.h"
#include "AdaptiveCarouselRenderer.h"
#include "AdaptiveCarouselRenderer.g.cpp"
#include "AdaptiveRenderArgs.h"
#include "WholeItemsPanel.h"
#include "XamlBuilder.h"
#include <windows.ui.xaml.data.h>

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::Microsoft::UI::Xaml::UIElement AdaptiveCarouselRenderer::Render(
        winrt::AdaptiveCards::ObjectModel::Xaml_Rendering::IAdaptiveCardElement const& element,
        winrt::AdaptiveCards::Rendering::Xaml_Rendering::AdaptiveRenderContext const& context,
        winrt::AdaptiveCards::Rendering::Xaml_Rendering::AdaptiveRenderArgs const& renderArgs)
    {
        auto carousel = element.as<winrt::IAdaptiveCarousel>();
        auto styledCollection = element.as<winrt::IAdaptiveContainerBase>();

        StackPanel stackPanel{};
        FlipView carouselUI{};
        bool loopEnabled{false};

        if (carousel.AutoLoop())
        {
            loopEnabled = carousel.AutoLoop().GetBoolean();
        }

        PipsPager pipsPager{};
        pipsPager.HorizontalAlignment(winrt::HorizontalAlignment::Center);
        pipsPager.NumberOfPages(carousel.Pages().Size());
        if (carousel.InitialPage())
        {
			pipsPager.SelectedPageIndex(carousel.InitialPage().GetInt32());
        }

        carouselUI.SelectionChanged([carouselUI, pipsPager](auto &&, auto &&) {
			pipsPager.SelectedPageIndex(carouselUI.SelectedIndex());
		});

        pipsPager.SelectedIndexChanged([carouselUI](winrt::PipsPager pager, winrt::IPipsPagerSelectedIndexChangedEventArgs) {
            carouselUI.SelectedIndex(pager.SelectedPageIndex());
        });

        stackPanel.Children().Append(carouselUI);
        stackPanel.Children().Append(pipsPager);

        winrt::AdaptiveFeatureRegistration featureRegistration = context.FeatureRegistration();
        boolean ancestorHasFallback = renderArgs.AncestorHasFallback();

        try
        {
			auto adaptiveCarousel = element.as<winrt::IAdaptiveCarousel>();

            winrt::Border carouselBorder{};

            auto gridContainer = winrt::make<winrt::implementation::WholeItemsPanel>();

            carouselBorder.Child(gridContainer);

            winrt::Border containerBorder{};

            auto containerStyle =
                XamlHelpers::HandleStylingAndPadding(styledCollection, containerBorder, context, renderArgs);

            auto newRenderArgs =
                winrt::make<winrt::implementation::AdaptiveRenderArgs>(containerStyle, renderArgs.ParentElement(), renderArgs);

            auto hostConfig = context.HostConfig();

			for (auto page : carousel.Pages())
            {
                auto [carouselPageUI, carouselPage] =
                    ::AdaptiveCards::Rendering::Xaml_Rendering::XamlBuilder::RenderAsUIElement(
                    page, context, newRenderArgs, featureRegistration, ancestorHasFallback);

                if (carouselPageUI != nullptr)
                {
                    carouselUI.Items().Append(carouselPageUI);

					carouselPageUI.try_as<FrameworkElement>().LayoutUpdated(
						[carouselUI](auto&&, auto&&) { SetFlipViewMaxHeight(carouselUI); });
                }
            }

            XamlHelpers::SetStyleFromResourceDictionary(context, L"Adaptive.Carousel", carouselUI);
            carouselUI.VerticalAlignment(winrt::VerticalAlignment::Stretch);

            auto selectAction = styledCollection.SelectAction();
            auto adaptiveBaseElement = element.try_as<winrt::IAdaptiveCardElement>();
            auto heightType = adaptiveBaseElement.Height();

            //auto columnSetMinHeight = adaptiveCarousel.MinHeight();
            //if (columnSetMinHeight > 0)
            //{
            //    gridContainer.MinHeight(columnSetMinHeight);
            //}

            XamlHelpers::AppendXamlElementToPanel(stackPanel, gridContainer, heightType);

			return gridContainer;
        }
        catch (winrt::hresult_error const& ex)
        {
            // In case we need to perform fallback, propagate it up to the parent
            if (ex.code() == E_PERFORM_FALLBACK)
            {
                throw ex;
            }

            XamlHelpers::ErrForRenderFailedForElement(context, element.ElementTypeString(), ex.message());
        }
		return nullptr;
    }

    void SetFlipViewMaxHeight(FlipView const& flipView)
	{
        auto selectIndex = flipView.SelectedIndex();
        auto carouselPageUI = flipView.Items().GetAt(selectIndex).try_as<FrameworkElement>();

        if (flipView.IsLoaded())
        {
            float width = static_cast<float>(flipView.ActualWidth());
            const winrt::Size noVerticalLimit{width, std::numeric_limits<float>::infinity()};
            carouselPageUI.Measure(noVerticalLimit);
            auto maxHeight = carouselPageUI.DesiredSize().Height;
            auto previousMaxHeight = flipView.MaxHeight();
            if ((std::numeric_limits<float>::infinity() == previousMaxHeight) || previousMaxHeight < maxHeight)
            {
                flipView.MaxHeight(maxHeight);
            }
        }
	}
}
