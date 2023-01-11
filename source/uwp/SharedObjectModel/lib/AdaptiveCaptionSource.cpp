// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCaptionSource.h"
#include "AdaptiveCaptionSource.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    AdaptiveCaptionSource::AdaptiveCaptionSource(std::shared_ptr<::AdaptiveCards::CaptionSource> const& sharedCaptionSource)
    {
        Label = UTF8ToHString(sharedCaptionSource->GetLabel());
        InitializeContentSource(sharedCaptionSource);
    }

    std::shared_ptr<::AdaptiveCards::CaptionSource> AdaptiveCaptionSource::GetSharedModel()
    {
        auto captionSource = std::make_shared<::AdaptiveCards::CaptionSource>();
        captionSource->SetMimeType(HStringToUTF8(MimeType));
        captionSource->SetUrl(HStringToUTF8(Url));
        captionSource->SetLabel(HStringToUTF8(Label));
        return captionSource;
    }
}
