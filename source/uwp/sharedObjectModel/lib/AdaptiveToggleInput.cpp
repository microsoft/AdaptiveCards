// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveToggleInput.h"
#include "AdaptiveToggleInput.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveToggleInput::AdaptiveToggleInput(const std::shared_ptr<::AdaptiveCards::ToggleInput>& sharedToggleInput)
    {
        Title = UTF8ToHString(sharedToggleInput->GetTitle());
        Value = UTF8ToHString(sharedToggleInput->GetValue());
        ValueOn = UTF8ToHString(sharedToggleInput->GetValueOn());
        ValueOff = UTF8ToHString(sharedToggleInput->GetValueOff());
        Wrap = sharedToggleInput->GetWrap();

        InitializeBaseElement(sharedToggleInput);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveToggleInput::GetSharedModel()
    {
        auto toggleInput = std::make_shared<::AdaptiveCards::ToggleInput>();
        CopySharedElementProperties(*toggleInput);

        toggleInput->SetTitle(HStringToUTF8(Title));
        toggleInput->SetValue(HStringToUTF8(Value));
        toggleInput->SetValueOn(HStringToUTF8(ValueOn));
        toggleInput->SetValueOff(HStringToUTF8(ValueOff));
        toggleInput->SetWrap(Wrap);

        return toggleInput;
    }
}
