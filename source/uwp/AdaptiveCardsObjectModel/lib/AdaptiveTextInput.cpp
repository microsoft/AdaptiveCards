// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextInput.h"
#include "AdaptiveTextInput.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveTextInput::AdaptiveTextInput(const std::shared_ptr<::AdaptiveCards::TextInput>& sharedTextInput)
    {
        Placeholder = UTF8ToHString(sharedTextInput->GetPlaceholder());
        Value = UTF8ToHString(sharedTextInput->GetValue());
        Regex = UTF8ToHString(sharedTextInput->GetRegex());
        MaxLength = sharedTextInput->GetMaxLength();
        IsMultiline = sharedTextInput->GetIsMultiline();
        TextInputStyle = static_cast<Uwp::TextInputStyle>(sharedTextInput->GetTextInputStyle());
        InlineAction = GenerateActionProjection(sharedTextInput->GetInlineAction());

        InitializeBaseElement(sharedTextInput);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveTextInput::GetSharedModel()
    {
        auto textInput = std::make_shared<::AdaptiveCards::TextInput>();
        CopySharedElementProperties(*textInput);

        textInput->SetMaxLength(MaxLength);
        textInput->SetIsMultiline(IsMultiline);
        textInput->SetTextInputStyle(static_cast<::AdaptiveCards::TextInputStyle>(TextInputStyle.get()));
        textInput->SetPlaceholder(HStringToUTF8(Placeholder));
        textInput->SetValue(HStringToUTF8(Value));
        textInput->SetRegex(HStringToUTF8(Regex));

        if (InlineAction.get())
        {
            textInput->SetInlineAction(GenerateSharedAction(InlineAction));
        }

        return textInput;
    }
}
