// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageSet.h"
#include "AdaptiveImageSet.g.cpp"
#include "AdaptiveImage.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveImageSet::AdaptiveImageSet(const std::shared_ptr<::AdaptiveCards::ImageSet>& sharedImageSet)
    {
        Images = GenerateVectorProjection<implementation::AdaptiveImage>(sharedImageSet->GetImages());
        ImageSize = static_cast<Uwp::ImageSize>(sharedImageSet->GetImageSize());
        InitializeBaseElement(sharedImageSet);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveImageSet::GetSharedModel()
    {
        auto imageSet = std::make_shared<::AdaptiveCards::ImageSet>();
        CopySharedElementProperties(*imageSet);
        imageSet->SetImageSize(static_cast<::AdaptiveCards::ImageSize>(ImageSize.get()));
        imageSet->GetImages() = GenerateSharedVector<implementation::AdaptiveImage, ::AdaptiveCards::Image>(Images.get());
        return imageSet;
    }
}
