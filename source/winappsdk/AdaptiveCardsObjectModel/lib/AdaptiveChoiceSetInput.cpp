// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveChoiceSetInput.h"
#include "AdaptiveChoiceInput.h"

#include "ObjectModelUtil.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation::Collections;

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    template<typename TRtType, typename TSharedType>
    winrt::Windows::Foundation::Collections::IVector<TRtType> GenerateVectorProjection(std::vector<std::shared_ptr<TSharedType>> const& items)
    {
        std::vector<TRtType> results;
        for (auto&& i : items)
        {
            results.emplace_back(winrt::make<TRtType>(i));
        }
        return winrt::single_threaded_vector<TRtType>(std::move(results));
    }

    AdaptiveChoiceSetInput::AdaptiveChoiceSetInput(std::shared_ptr<::AdaptiveCards::ChoiceSetInput> const& sharedChoiceSetInput) :
        implementation::AdaptiveInputElementBase(ElementType::ChoiceSetInput)
    {
        Choices = GenerateVectorProjection<implementation::AdaptiveChoiceSetInput>(sharedChoiceSetInput);
        IsMultiSelect = sharedChoiceSetInput->GetIsMultiSelect();
        Wrap = sharedChoiceSetInput->GetWrap();
        ChoiceSetStyle =
            static_cast<ABI::AdaptiveCards::ObjectModel::WinUI3::ChoiceSetStyle>(sharedChoiceSetInput->GetChoiceSetStyle());
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
        choiceSet->GetChoices() = GenerateSharedVector<WinUI3::AdaptiveChoiceInput, ::AdaptiveCards::ChoiceInput>(Choices);

        return choiceSet;
    }
}
