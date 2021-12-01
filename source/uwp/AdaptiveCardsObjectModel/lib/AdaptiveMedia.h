// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCardElement.h"
#include "Media.h"
#include "AdaptiveMedia.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("0c87566c-a58c-4332-8b3b-79c9714074f6") AdaptiveMedia : AdaptiveMediaT<AdaptiveMedia, ITypePeek>, AdaptiveCardElementBase
    {
        AdaptiveMedia(const std::shared_ptr<::AdaptiveCards::Media>& sharedMedia = std::make_shared<::AdaptiveCards::Media>());

        property<hstring> Poster;
        property<hstring> AltText;
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveMediaSource>> Sources;

        auto ElementType() { return winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::Media; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveMedia : AdaptiveMediaT<AdaptiveMedia, implementation::AdaptiveMedia>
    {
    };
}
