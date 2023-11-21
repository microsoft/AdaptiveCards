#include "pch.h"
#include "AdaptiveCarouselPage.h"
#include "AdaptiveCarouselPage.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    AdaptiveCarouselPage::AdaptiveCarouselPage(const std::shared_ptr<::AdaptiveCards::CarouselPage>& sharedCarouselPage)
    {
        VerticalContentAlignment = opt_cast<Xaml_OM::VerticalContentAlignment>(sharedCarouselPage->GetVerticalContentAlignment());
        Items = GenerateContainedElementsProjection(sharedCarouselPage->GetItems());
        SelectAction = GenerateActionProjection(sharedCarouselPage->GetSelectAction());
        Style = static_cast<Xaml_OM::ContainerStyle>(sharedCarouselPage->GetStyle());
        MinHeight = sharedCarouselPage->GetMinHeight();
        Bleed = sharedCarouselPage->GetBleed();
        BleedDirection = static_cast<Xaml_OM::BleedDirection>(sharedCarouselPage->GetBleedDirection());
        Rtl = sharedCarouselPage->GetRtl();

        auto backgroundImage = sharedCarouselPage->GetBackgroundImage();
        if (backgroundImage && !backgroundImage->GetUrl().empty())
        {
            BackgroundImage = winrt::make<implementation::AdaptiveBackgroundImage>(backgroundImage);
        }

        InitializeBaseElement(sharedCarouselPage);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveCarouselPage::GetSharedModel()
    {
        auto carouselPage = std::make_shared<::AdaptiveCards::Container>();
        CopySharedElementProperties(*carouselPage);

        if (SelectAction.get())
        {
            carouselPage->SetSelectAction(GenerateSharedAction(SelectAction.get()));
        }

        if (VerticalContentAlignment)
        {
            carouselPage->SetVerticalContentAlignment(VerticalContentAlignment.get<::AdaptiveCards::VerticalContentAlignment>());
        }

        carouselPage->SetStyle(static_cast<::AdaptiveCards::ContainerStyle>(Style.get()));
        carouselPage->SetMinHeight(MinHeight);

        if (auto adaptiveBackgroundImage = peek_innards<implementation::AdaptiveBackgroundImage>(BackgroundImage.get()))
        {
            if (auto sharedBackgroundImage = adaptiveBackgroundImage->GetSharedModel())
            {
                carouselPage->SetBackgroundImage(sharedBackgroundImage);
            }
        }

        carouselPage->SetBleed(Bleed);
        carouselPage->SetRtl(Rtl);
        carouselPage->GetItems() = GenerateSharedElements(Items.get());

        return carouselPage;
    }
}
