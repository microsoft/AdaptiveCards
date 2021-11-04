// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveChoiceSetInput.h"
#include "AdaptiveChoiceSetInput.g.cpp"
#include "AdaptiveChoiceInput.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveChoiceSetInput::AdaptiveChoiceSetInput(std::shared_ptr<::AdaptiveCards::ChoiceSetInput> const& sharedChoiceSetInput)
    {
        Choices = GenerateVectorProjection<implementation::AdaptiveChoiceInput>(sharedChoiceSetInput->GetChoices());
        IsMultiSelect = sharedChoiceSetInput->GetIsMultiSelect();
        Wrap = sharedChoiceSetInput->GetWrap();
        ChoiceSetStyle = static_cast<Uwp::ChoiceSetStyle>(sharedChoiceSetInput->GetChoiceSetStyle());
        Value = UTF8ToHString(sharedChoiceSetInput->GetValue());
        Placeholder = UTF8ToHString(sharedChoiceSetInput->GetPlaceholder());

        InitializeBaseElement(sharedChoiceSetInput);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveChoiceSetInput::GetSharedModel()
    {
        auto choiceSet = std::make_shared<::AdaptiveCards::ChoiceSetInput>();
        CopySharedElementProperties(*choiceSet);

        choiceSet->SetChoiceSetStyle(static_cast<::AdaptiveCards::ChoiceSetStyle>(ChoiceSetStyle.get()));
        choiceSet->SetIsMultiSelect(IsMultiSelect);
        choiceSet->SetValue(HStringToUTF8(Value));
        choiceSet->SetWrap(Wrap);
        choiceSet->SetPlaceholder(HStringToUTF8(Placeholder));
        choiceSet->GetChoices() = GenerateSharedVector<implementation::AdaptiveChoiceInput, ::AdaptiveCards::ChoiceInput>(Choices.get());

        return choiceSet;
    }
}
