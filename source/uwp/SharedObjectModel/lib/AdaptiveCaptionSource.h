// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveContentSource.h"
#include "CaptionSource.h"
#include "AdaptiveCaptionSource.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct DECLSPEC_UUID("64A2DA59-EFA4-47E3-B704-9B3777DE2907") AdaptiveCaptionSource
        : AdaptiveCaptionSourceT<AdaptiveCaptionSource, ITypePeek>, AdaptiveContentSource
    {
        AdaptiveCaptionSource(std::shared_ptr<::AdaptiveCards::CaptionSource> const& sharedCaptionSource =
                                std::make_shared<::AdaptiveCards::CaptionSource>());

        property<hstring> Label;

        virtual std::shared_ptr<::AdaptiveCards::CaptionSource> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveCaptionSource : AdaptiveCaptionSourceT<AdaptiveCaptionSource, implementation::AdaptiveCaptionSource>
    {
    };
}
