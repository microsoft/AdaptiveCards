// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRichTextBlock.h"
#include "AdaptiveRichTextBlock.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveRichTextBlock::AdaptiveRichTextBlock(const std::shared_ptr<::AdaptiveCards::RichTextBlock>& sharedRichTextBlock) noexcept
    {
        HorizontalAlignment = opt_cast<Uwp::HAlignment>(sharedRichTextBlock->GetHorizontalAlignment());
        Inlines = GenerateInlinesProjection(sharedRichTextBlock->GetInlines());

        InitializeBaseElement(sharedRichTextBlock);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveRichTextBlock::GetSharedModel()
    {
        auto richTextBlock = std::make_shared<::AdaptiveCards::RichTextBlock>();
        CopySharedElementProperties(*richTextBlock);
        richTextBlock->SetHorizontalAlignment(HorizontalAlignment.get<::AdaptiveCards::HorizontalAlignment>());
        richTextBlock->GetInlines() = GenerateSharedInlines(Inlines);
        return richTextBlock;
    }
}
