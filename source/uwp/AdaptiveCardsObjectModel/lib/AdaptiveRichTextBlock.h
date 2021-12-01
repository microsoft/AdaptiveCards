// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "RichTextBlock.h"
#include "AdaptiveRichTextBlock.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("0c87566c-a58c-4332-8b3b-79c9714074f6") AdaptiveRichTextBlock : AdaptiveRichTextBlockT<AdaptiveRichTextBlock, ITypePeek>, AdaptiveCardElementBase
    {
        AdaptiveRichTextBlock(const std::shared_ptr<::AdaptiveCards::RichTextBlock>& sharedRichTextBlock = std::make_shared<::AdaptiveCards::RichTextBlock>()) noexcept;

        // IAdaptiveRichTextBlock
        property_opt<Uwp::HAlignment> HorizontalAlignment;
        property<winrt::Windows::Foundation::Collections::IVector<Uwp::IAdaptiveInline>> Inlines;

        // IAdaptiveCardElement
        auto ElementType() { return ElementType::RichTextBlock; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveRichTextBlock : AdaptiveRichTextBlockT<AdaptiveRichTextBlock, implementation::AdaptiveRichTextBlock>
    {
    };
}
