#pragma once

#include "AdaptiveBackgroundImage.h"
#include "AdaptiveCarouselPage.g.h"
#include "Carousel.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct DECLSPEC_UUID("4DFACDD1-355B-40E0-AC89-5919022784D7") AdaptiveCarouselPage :
        AdaptiveCarouselPageT<AdaptiveCarouselPage, ITypePeek>, AdaptiveCardElementBase
    {
        AdaptiveCarouselPage(const std::shared_ptr<::AdaptiveCards::CarouselPage>&
            sharedCarouselPage = std::make_shared<::AdaptiveCards::CarouselPage>());

        // IAdaptiveCardElement
        auto ElementType()
        {
            return ElementType::CarouselPage;
        }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        property<winrt::Windows::Foundation::Collections::IVector<Xaml_OM::IAdaptiveCardElement>> Items;
        property<Xaml_OM::IAdaptiveActionElement> SelectAction;
        property<Xaml_OM::ContainerStyle> Style;
        property_opt<Xaml_OM::VerticalContentAlignment> VerticalContentAlignment;
        property<Xaml_OM::AdaptiveBackgroundImage> BackgroundImage{nullptr};
        property<uint32_t> MinHeight;
        property<bool> Bleed;
        property<Xaml_OM::BleedDirection> BleedDirection;
        property_opt<bool> Rtl;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveCarouselPage : AdaptiveCarouselPageT<AdaptiveCarouselPage, implementation::AdaptiveCarouselPage>
    {
    };
}
