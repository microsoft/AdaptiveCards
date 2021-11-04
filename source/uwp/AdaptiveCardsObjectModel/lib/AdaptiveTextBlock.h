// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TextBlock.h"
#include "AdaptiveTextElement.h"
#include "AdaptiveTextBlock.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("0c87566c-a58c-4332-8b3b-79c9714074f6") AdaptiveTextBlock : AdaptiveTextBlockT<AdaptiveTextBlock, ITypePeek>, AdaptiveCardElementBase, AdaptiveTextElement
    {
        AdaptiveTextBlock(const std::shared_ptr<::AdaptiveCards::TextBlock>& sharedTextBlock = std::make_shared<::AdaptiveCards::TextBlock>());

        property<bool> Wrap;
        property<uint32_t> MaxLines;
        property_opt<Uwp::HAlignment> HorizontalAlignment;
        property_opt<Uwp::TextStyle> Style;

        auto ElementType() { return ElementType::TextBlock; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveTextBlock : AdaptiveTextBlockT<AdaptiveTextBlock, implementation::AdaptiveTextBlock>
    {
    };
}
