// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextBlock.h"
#include "AdaptiveTextBlock.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveTextBlock::AdaptiveTextBlock(const std::shared_ptr<::AdaptiveCards::TextBlock>& sharedTextBlock)
    {
        Wrap = sharedTextBlock->GetWrap();
        MaxLines = sharedTextBlock->GetMaxLines();

        if (sharedTextBlock->GetHorizontalAlignment().has_value())
        {
            HorizontalAlignment =
                winrt::box_value(static_cast<Uwp::HAlignment>(sharedTextBlock->GetHorizontalAlignment().value()))
                    .as<Windows::Foundation::IReference<Uwp::HAlignment>>();
        }

        if (sharedTextBlock->GetStyle().has_value())
        {
            Style = winrt::box_value(static_cast<Uwp::TextStyle>(sharedTextBlock->GetStyle().value()))
                        .as<Windows::Foundation::IReference<Uwp::TextStyle>>();
        }

        InitializeTextElement(sharedTextBlock);
        InitializeBaseElement(sharedTextBlock);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveTextBlock::GetSharedModel()
    {
        auto textBlock = std::make_shared<::AdaptiveCards::TextBlock>();
        CopySharedElementProperties(*textBlock);
        CopyTextElementProperties(*textBlock);

        textBlock->SetWrap(Wrap);
        textBlock->SetMaxLines(MaxLines);
        textBlock->SetHorizontalAlignment(HorizontalAlignment.get<::AdaptiveCards::HorizontalAlignment>());
        textBlock->SetStyle(Style.get<::AdaptiveCards::TextStyle>());

        return textBlock;
    }
}
