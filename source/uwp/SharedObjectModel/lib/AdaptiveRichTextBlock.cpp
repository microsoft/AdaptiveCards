// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRichTextBlock.h"
#include "AdaptiveRichTextBlock.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    AdaptiveRichTextBlock::AdaptiveRichTextBlock(const std::shared_ptr<::AdaptiveCards::RichTextBlock>& sharedRichTextBlock) noexcept
    {
        HorizontalAlignment = opt_cast<Xaml_OM::HAlignment>(sharedRichTextBlock->GetHorizontalAlignment());
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
