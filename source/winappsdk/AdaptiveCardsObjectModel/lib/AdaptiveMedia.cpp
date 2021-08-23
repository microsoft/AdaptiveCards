// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveMedia.h"
#include "AdaptiveMediaSource.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    AdaptiveMedia::AdaptiveMedia(const std::shared_ptr<::AdaptiveCards::Media>& sharedMedia)
    {
        Poster = UTF8ToHString(sharedMedia->GetPoster());
        AltText = UTF8ToHString(sharedMedia->GetAltText());
        Sources = GenerateVectorProjection<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveMediaSource>(sharedMedia->GetSources());
        InitializeBaseElement(sharedMedia);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveMedia::GetSharedModel()
    {
        auto media = std::make_shared<::AdaptiveCards::Media>();
        CopySharedElementProperties(*media);
        media->SetPoster(HStringToUTF8(Poster));
        media->SetAltText(HStringToUTF8(AltText));
        media->GetSources() =
            GenerateSharedVector<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveMediaSource, ::AdaptiveCards::MediaSource>(Sources.get());

        return media;
    }
}
