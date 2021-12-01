// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TextInput.h"
#include "AdaptiveInputElement.h"
#include "AdaptiveTextInput.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("2e716e94-a83a-4e9b-9873-bff858af068d") AdaptiveTextInput : AdaptiveTextInputT<AdaptiveTextInput, ITypePeek>, AdaptiveInputElementBase
    {
        AdaptiveTextInput(const std::shared_ptr<::AdaptiveCards::TextInput>& sharedTextInput = std::make_shared<::AdaptiveCards::TextInput>());

        // IAdaptiveTextInput
        property<hstring> Placeholder;
        property<hstring> Value;
        property<bool> IsMultiline;
        property<uint32_t> MaxLength;
        property<Uwp::TextInputStyle> TextInputStyle;
        property<Uwp::IAdaptiveActionElement> InlineAction;
        property<hstring> Regex;

        auto ElementType() { return ElementType::TextInput; }

        std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveTextInput : AdaptiveTextInputT<AdaptiveTextInput, implementation::AdaptiveTextInput>
    {
    };
}
