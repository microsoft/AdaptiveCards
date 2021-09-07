// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveBackgroundImage.h"
#include "AdaptiveBackgroundImage.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveBackgroundImage::AdaptiveBackgroundImage(const std::shared_ptr<::AdaptiveCards::BackgroundImage>& sharedImage)
    {
        Url = UTF8ToHString(sharedImage->GetUrl());
        FillMode = static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::BackgroundImageFillMode>(sharedImage->GetFillMode());
        HorizontalAlignment = static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::HAlignment>(sharedImage->GetHorizontalAlignment());
        VerticalAlignment = static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::VAlignment>(sharedImage->GetVerticalAlignment());
    }

    std::shared_ptr<::AdaptiveCards::BackgroundImage> AdaptiveBackgroundImage::GetSharedModel()
    {
        auto image = std::make_shared<::AdaptiveCards::BackgroundImage>();

        image->SetUrl(HStringToUTF8(Url));
        image->SetFillMode(static_cast<::AdaptiveCards::ImageFillMode>(FillMode.get()));
        image->SetHorizontalAlignment(static_cast<::AdaptiveCards::HorizontalAlignment>(HorizontalAlignment.get()));
        image->SetVerticalAlignment(static_cast<::AdaptiveCards::VerticalAlignment>(VerticalAlignment.get()));

        return image;
    }
}
