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
        HeightInPixels = sharedCarousel->GetHeightInPixels();
        InitialPage = sharedCarousel->GetInitialPage();
        AutoLoop = sharedCarousel->GetAutoLoop();

        MinHeight = sharedCarousel->GetMinHeight();
        Rtl = sharedCarousel->GetRtl();
        Bleed = sharedCarousel->GetBleed();
        BleedDirection = static_cast<Xaml_OM::BleedDirection>(sharedCarousel->GetBleedDirection());
        SelectAction = GenerateActionProjection(sharedCarousel->GetSelectAction());
        Style = static_cast<Xaml_OM::ContainerStyle>(sharedCarousel->GetStyle());
        VerticalContentAlignment = opt_cast<Xaml_OM::VerticalContentAlignment>(sharedCarousel->GetVerticalContentAlignment());

        auto backgroundImage = sharedCarousel->GetBackgroundImage();
        if (backgroundImage && !backgroundImage->GetUrl().empty())
        {
            BackgroundImage = winrt::make<implementation::AdaptiveBackgroundImage>(backgroundImage);
        }

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
        carousel->SetHeightInPixels(HeightInPixels);
		carousel->SetInitialPage(InitialPage);
        carousel->setAutoLoop(AutoLoop);
        carousel->SetBleed(Bleed);
        carousel->SetMinHeight(MinHeight);

        if (SelectAction.get())
        {
            carousel->SetSelectAction(GenerateSharedAction(SelectAction.get()));
        }

        if (VerticalContentAlignment)
        {
            carousel->SetVerticalContentAlignment(VerticalContentAlignment.get<::AdaptiveCards::VerticalContentAlignment>());
        }

        if (auto adaptiveBackgroundImage = peek_innards<implementation::AdaptiveBackgroundImage>(BackgroundImage.get()))
        {
            if (auto sharedBackgroundImage = adaptiveBackgroundImage->GetSharedModel())
            {
                carousel->SetBackgroundImage(sharedBackgroundImage);
            }
        }

        return carousel;
    }
}
