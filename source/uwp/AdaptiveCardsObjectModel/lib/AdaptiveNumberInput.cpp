// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveNumberInput.h"
#include "AdaptiveNumberInput.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveNumberInput::AdaptiveNumberInput(const std::shared_ptr<::AdaptiveCards::NumberInput>& sharedNumberInput)
    {
        if (sharedNumberInput->GetMin().has_value())
        {
            Min = winrt::box_value(sharedNumberInput->GetMin().value()).as<Windows::Foundation::IReference<double>>();
        }

        if (sharedNumberInput->GetMax().has_value())
        {
            Max = winrt::box_value(sharedNumberInput->GetMax().value()).as<Windows::Foundation::IReference<double>>();
        }

        if (sharedNumberInput->GetValue().has_value())
        {
            Value = winrt::box_value(sharedNumberInput->GetValue().value()).as<Windows::Foundation::IReference<double>>();
        }

        Placeholder = UTF8ToHString(sharedNumberInput->GetPlaceholder());
        InitializeBaseElement(sharedNumberInput);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveNumberInput::GetSharedModel()
    {
        auto numberInput = std::make_shared<::AdaptiveCards::NumberInput>();
        CopySharedElementProperties(*numberInput);

        numberInput->SetMax(Max);
        numberInput->SetMin(Min);
        numberInput->SetValue(Value);
        numberInput->SetPlaceholder(HStringToUTF8(Placeholder));

        return numberInput;
    }
}
