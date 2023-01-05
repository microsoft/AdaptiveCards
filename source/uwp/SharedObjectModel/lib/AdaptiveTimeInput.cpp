// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTimeInput.h"
#include "AdaptiveTimeInput.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveTimeInput::AdaptiveTimeInput(const std::shared_ptr<::AdaptiveCards::TimeInput>& sharedTimeInput)
    {
        Max = UTF8ToHString(sharedTimeInput->GetMax());
        Min = UTF8ToHString(sharedTimeInput->GetMin());
        Placeholder = UTF8ToHString(sharedTimeInput->GetPlaceholder());
        Value = UTF8ToHString(sharedTimeInput->GetValue());

        InitializeBaseElement(sharedTimeInput);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveTimeInput::GetSharedModel()
    {
        auto timeInput = std::make_shared<::AdaptiveCards::TimeInput>();
        CopySharedElementProperties(*timeInput);

        timeInput->SetMax(HStringToUTF8(Max));
        timeInput->SetMin(HStringToUTF8(Min));
        timeInput->SetPlaceholder(HStringToUTF8(Placeholder));
        timeInput->SetValue(HStringToUTF8(Value));

        return timeInput;
    }
}
