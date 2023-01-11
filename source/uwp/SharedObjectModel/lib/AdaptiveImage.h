// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Image.h"
#include "AdaptiveImage.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("c940ac19-5faa-47f3-9d4b-f4d8e7d6ec1d") AdaptiveImage : AdaptiveImageT<AdaptiveImage, ITypePeek>, AdaptiveCardElementBase
    {
        AdaptiveImage(const std::shared_ptr<::AdaptiveCards::Image>& sharedImage = std::make_shared<::AdaptiveCards::Image>());

        // IAdaptiveImage
        property<hstring> Url;
        property<hstring> BackgroundColor;
        property<Uwp::ImageStyle> Style;
        property<Uwp::ImageSize> Size;
        property<uint32_t> PixelWidth;
        property<uint32_t> PixelHeight;
        property<hstring> AltText;
        property_opt<Uwp::HAlignment> HorizontalAlignment;
        property<Uwp::IAdaptiveActionElement> SelectAction;

        // IAdaptiveCardElement
        auto ElementType() { return ElementType::Image; }

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel();
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveImage : AdaptiveImageT<AdaptiveImage, implementation::AdaptiveImage>
    {
    };
}
