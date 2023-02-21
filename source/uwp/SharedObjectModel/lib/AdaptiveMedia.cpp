// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveMedia.h"
#include "AdaptiveMedia.g.cpp"
#include "AdaptiveMediaSource.h"
#include "AdaptiveCaptionSource.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    AdaptiveMedia::AdaptiveMedia(const std::shared_ptr<::AdaptiveCards::Media>& sharedMedia)
    {
        Poster = UTF8ToHString(sharedMedia->GetPoster());
        AltText = UTF8ToHString(sharedMedia->GetAltText());
        Sources = GenerateVectorProjection<winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation::AdaptiveMediaSource>(sharedMedia->GetSources());
        CaptionSources = GenerateVectorProjection<winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation::AdaptiveCaptionSource>(sharedMedia->GetCaptionSources());
        InitializeBaseElement(sharedMedia);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveMedia::GetSharedModel()
    {
        auto media = std::make_shared<::AdaptiveCards::Media>();
        CopySharedElementProperties(*media);
        media->SetPoster(HStringToUTF8(Poster));
        media->SetAltText(HStringToUTF8(AltText));
        media->GetSources() =
            GenerateSharedVector<winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation::AdaptiveMediaSource, ::AdaptiveCards::MediaSource>(Sources.get());
        media->GetCaptionSources() =
            GenerateSharedVector<winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation::AdaptiveCaptionSource, ::AdaptiveCards::CaptionSource>(CaptionSources.get());

        return media;
    }
}
