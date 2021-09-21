// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextRun.h"
#include "AdaptiveTextRun.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveTextRun::AdaptiveTextRun(const std::shared_ptr<::AdaptiveCards::TextRun>& sharedTextRun)
    {
        Highlight = sharedTextRun->GetHighlight();
        Italic = sharedTextRun->GetItalic();
        Strikethrough = sharedTextRun->GetStrikethrough();
        Underline = sharedTextRun->GetUnderline();
        SelectAction = GenerateActionProjection(sharedTextRun->GetSelectAction());
        InitializeTextElement(sharedTextRun);
    }

    std::shared_ptr<::AdaptiveCards::TextRun> AdaptiveTextRun::GetSharedModel()
    {
        auto textRun = std::make_shared<::AdaptiveCards::TextRun>();
        CopyTextElementProperties(*textRun);

        textRun->SetItalic(Italic);
        textRun->SetStrikethrough(Strikethrough);
        textRun->SetHighlight(Highlight);
        textRun->SetUnderline(Underline);

        if (SelectAction.get())
        {
            textRun->SetSelectAction(GenerateSharedAction(SelectAction));
        }

        return textRun;
    }
}
