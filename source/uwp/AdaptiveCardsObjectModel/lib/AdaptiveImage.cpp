// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImage.h"
#include "AdaptiveImage.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveImage::AdaptiveImage(const std::shared_ptr<::AdaptiveCards::Image>& sharedImage)
    {
        Url = UTF8ToHString(sharedImage->GetUrl());
        BackgroundColor = UTF8ToHString(sharedImage->GetBackgroundColor());
        Style = static_cast<Uwp::ImageStyle>(sharedImage->GetImageStyle());
        Size = static_cast<Uwp::ImageSize>(sharedImage->GetImageSize());
        PixelWidth = sharedImage->GetPixelWidth();
        PixelHeight = sharedImage->GetPixelHeight();
        AltText = UTF8ToHString(sharedImage->GetAltText());
        SelectAction = GenerateActionProjection(sharedImage->GetSelectAction());
        HorizontalAlignment = opt_cast<Uwp::HAlignment>(sharedImage->GetHorizontalAlignment());

        InitializeBaseElement(sharedImage);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveImage::GetSharedModel()
    {
        auto image = std::make_shared<::AdaptiveCards::Image>();
        CopySharedElementProperties(*image);

        if (SelectAction.get())
        {
            image->SetSelectAction(GenerateSharedAction(SelectAction.get()));
        }

        image->SetUrl(HStringToUTF8(Url));
        image->SetBackgroundColor(HStringToUTF8(BackgroundColor));

        if (!AltText.get().empty())
        {
            image->SetAltText(HStringToUTF8(AltText));
        }

        image->SetImageStyle(static_cast<::AdaptiveCards::ImageStyle>(Style.get()));
        image->SetImageSize(static_cast<::AdaptiveCards::ImageSize>(Size.get()));
        image->SetPixelHeight(PixelHeight);
        image->SetPixelWidth(PixelWidth);
        image->SetHorizontalAlignment(HorizontalAlignment.get<::AdaptiveCards::HorizontalAlignment>());

        return image;
    }
}
