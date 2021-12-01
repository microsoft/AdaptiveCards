// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ImageSet.h"
#include "AdaptiveImageSet.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("04ed4200-de21-4587-8bc5-74b000809985") AdaptiveImageSet : AdaptiveImageSetT<AdaptiveImageSet, ITypePeek>, AdaptiveCardElementBase
    {
        AdaptiveImageSet(const std::shared_ptr<::AdaptiveCards::ImageSet>& sharedImageSet = std::make_shared<::AdaptiveCards::ImageSet>());

        property<winrt::Windows::Foundation::Collections::IVector<Uwp::AdaptiveImage>> Images;
        property<Uwp::ImageSize> ImageSize;

        // IAdaptiveCardElement
        auto ElementType() { return ElementType::ImageSet; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveImageSet : AdaptiveImageSetT<AdaptiveImageSet, implementation::AdaptiveImageSet>
    {
    };
}
