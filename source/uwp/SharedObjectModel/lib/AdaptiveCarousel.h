#pragma once
#include "AdaptiveCarousel.g.h"
#include "AdaptiveCarouselPage.h"
#include "Carousel.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct DECLSPEC_UUID("BF10C7E9-E525-4EFB-9F1E-CCE6ABB1C226") AdaptiveCarousel : AdaptiveCarouselT<AdaptiveCarousel, ITypePeek>, AdaptiveCardElementBase
    {
        AdaptiveCarousel(const std::shared_ptr<::AdaptiveCards::Carousel>&
            sharedcontainer = std::make_shared<::AdaptiveCards::Carousel>());

        property<winrt::Windows::Foundation::Collections::IVector<Xaml_OM::AdaptiveCarouselPage>> Pages;

        property<Xaml_OM::CarouselOrientation> Orientation;
        property<hstring> HeightInPixels;
        property_opt<uint64_t> Timer;
        property_opt<uint32_t> InitialPage;
        property_opt<bool> AutoLoop;
        property<uint32_t> MinHeight;

        property_opt<bool> Rtl;
        property<bool> Bleed;
        property<Xaml_OM::BleedDirection> BleedDirection;
        property<Xaml_OM::IAdaptiveActionElement> SelectAction;
        property<Xaml_OM::ContainerStyle> Style;

        // IAdaptiveCardElement
        auto ElementType() { return Xaml_OM::ElementType::Carousel; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveCarousel : AdaptiveCarouselT<AdaptiveCarousel, implementation::AdaptiveCarousel>
    {
    };
}
