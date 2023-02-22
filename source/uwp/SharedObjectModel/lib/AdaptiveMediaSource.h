// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveContentSource.h"
#include "MediaSource.h"
#include "AdaptiveMediaSource.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct DECLSPEC_UUID("0c87566c-a58c-4332-8b3b-79c9714074f6") AdaptiveMediaSource
        : AdaptiveMediaSourceT<AdaptiveMediaSource, ITypePeek>, AdaptiveContentSource
    {
        AdaptiveMediaSource(std::shared_ptr<::AdaptiveCards::MediaSource> const& sharedMediaSource =
                                std::make_shared<::AdaptiveCards::MediaSource>());

        virtual std::shared_ptr<::AdaptiveCards::MediaSource> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveMediaSource : AdaptiveMediaSourceT<AdaptiveMediaSource, implementation::AdaptiveMediaSource>
    {
    };
}
