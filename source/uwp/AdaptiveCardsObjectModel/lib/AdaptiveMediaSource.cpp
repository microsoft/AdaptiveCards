// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveMediaSource.h"
#include "AdaptiveMediaSource.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveMediaSource::AdaptiveMediaSource(const std::shared_ptr<::AdaptiveCards::MediaSource>& sharedMediaSource)
    {
        MimeType = UTF8ToHString(sharedMediaSource->GetMimeType());
        Url = UTF8ToHString(sharedMediaSource->GetUrl());
    }

    std::shared_ptr<::AdaptiveCards::MediaSource> AdaptiveMediaSource::GetSharedModel()
    {
        auto mediaSource = std::make_shared<::AdaptiveCards::MediaSource>();
        mediaSource->SetMimeType(HStringToUTF8(MimeType));
        mediaSource->SetUrl(HStringToUTF8(Url));
        return mediaSource;
    }
}
