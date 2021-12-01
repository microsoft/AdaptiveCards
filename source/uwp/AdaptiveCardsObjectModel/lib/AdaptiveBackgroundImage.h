// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "BackgroundImage.h"
#include "AdaptiveBackgroundImage.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("60F8A683-A7A3-4E34-BE86-C809F61BD5B6") AdaptiveBackgroundImage
        : AdaptiveBackgroundImageT<AdaptiveBackgroundImage, ITypePeek>
    {
        AdaptiveBackgroundImage(const std::shared_ptr<::AdaptiveCards::BackgroundImage>& sharedImage =
                                    std::make_shared<::AdaptiveCards::BackgroundImage>());

        property<hstring> Url;
        property<Uwp::BackgroundImageFillMode> FillMode;
        property<Uwp::HAlignment> HorizontalAlignment;
        property<Uwp::VAlignment> VerticalAlignment;

        std::shared_ptr<::AdaptiveCards::BackgroundImage> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveBackgroundImage : AdaptiveBackgroundImageT<AdaptiveBackgroundImage, implementation::AdaptiveBackgroundImage>
    {
    };
}
