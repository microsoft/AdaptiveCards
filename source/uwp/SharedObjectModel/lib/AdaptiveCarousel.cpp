#include "pch.h"
#include "AdaptiveCarousel.h"
#include "AdaptiveCarousel.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    AdaptiveCarousel::AdaptiveCarousel(const std::shared_ptr<::AdaptiveCards::Carousel>& sharedCarousel)
    {
        Pages = GenerateVectorProjection<implementation::AdaptiveCarouselPage>(sharedCarousel->GetPages());
        Rtl = sharedCarousel->GetRtl();

        Orientation = static_cast<Xaml_OM::CarouselOrientation>(
            sharedCarousel->GetOrientation().value_or(::AdaptiveCards::CarouselOrientation::Horizontal));
        Timer = sharedCarousel->GetTimer();
        HeightInPixels = UTF8ToHString(sharedCarousel->GetHeightInPixels());
        InitialPage = sharedCarousel->GetInitialPage();
        AutoLoop = sharedCarousel->GetAutoLoop();

        Rtl = false;
        Bleed = false;
        BleedDirection = BleedDirection::All;
        SelectAction = nullptr;
        Style = ContainerStyle::None;

        InitializeBaseElement(sharedCarousel);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveCarousel::GetSharedModel()
    {
        auto carousel = std::make_shared<::AdaptiveCards::Carousel>();
        CopySharedElementProperties(*carousel);

        carousel->GetPages() = GenerateSharedVector<implementation::AdaptiveCarouselPage, ::AdaptiveCards::CarouselPage>(Pages.get());
        carousel->SetRtl(Rtl);
        carousel->SetOrientation(static_cast<::AdaptiveCards::CarouselOrientation>(Orientation.get()));
        carousel->SetTimer(Timer);
        carousel->SetHeightInPixels(HStringToUTF8(HeightInPixels));
		carousel->SetInitialPage(InitialPage);
        carousel->setAutoLoop(AutoLoop);
        return carousel;
    }
}
