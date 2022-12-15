// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveDateInput.h"
#include "AdaptiveDateInput.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveDateInput::AdaptiveDateInput(const std::shared_ptr<::AdaptiveCards::DateInput>& sharedDateInput)
    {
        Max = UTF8ToHString(sharedDateInput->GetMax());
        Min = UTF8ToHString(sharedDateInput->GetMin());
        Placeholder = UTF8ToHString(sharedDateInput->GetPlaceholder());
        Value = UTF8ToHString(sharedDateInput->GetValue());

        InitializeBaseElement(sharedDateInput);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveDateInput::GetSharedModel()
    {
        auto dateInput = std::make_shared<::AdaptiveCards::DateInput>();
        CopySharedElementProperties(*dateInput);

        dateInput->SetMax(HStringToUTF8(Max));
        dateInput->SetMin(HStringToUTF8(Min));
        dateInput->SetPlaceholder(HStringToUTF8(Placeholder));
        dateInput->SetValue(HStringToUTF8(Value));

        return dateInput;
    }
}
