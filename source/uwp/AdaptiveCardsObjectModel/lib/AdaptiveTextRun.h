// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TextRun.h"
#include "AdaptiveTextElement.h"
#include "AdaptiveTextRun.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("d37e5b66-2a5e-4a9e-b087-dbef5a1705b1") AdaptiveTextRun : AdaptiveTextRunT<AdaptiveTextRun, ITypePeek>, AdaptiveTextElement
    {
        AdaptiveTextRun(const std::shared_ptr<::AdaptiveCards::TextRun>& sharedTextRun = std::make_shared<::AdaptiveCards::TextRun>());

        // IAdaptiveTextRun
        property<bool> Highlight;
        property<Uwp::IAdaptiveActionElement> SelectAction;
        property<bool> Italic;
        property<bool> Strikethrough;
        property<bool> Underline;

        std::shared_ptr<::AdaptiveCards::TextRun> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveTextRun : AdaptiveTextRunT<AdaptiveTextRun, implementation::AdaptiveTextRun>
    {
    };
}
