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
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    AdaptiveChoiceSetInput::AdaptiveChoiceSetInput()
    {
        m_choices = Microsoft::WRL::Make<Vector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveChoiceInput*>>();
    }

    HRESULT AdaptiveChoiceSetInput::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::ChoiceSetInput> choiceSet = std::make_shared<AdaptiveCards::ChoiceSetInput>();
        return RuntimeClassInitialize(choiceSet);
    }
    CATCH_RETURN;

    HRESULT AdaptiveChoiceSetInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ChoiceSetInput>& sharedChoiceSetInput)
    try
    {
        if (sharedChoiceSetInput == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateInputChoicesProjection(sharedChoiceSetInput->GetChoices(), m_choices.Get());

        m_isMultiSelect = sharedChoiceSetInput->GetIsMultiSelect();
        m_wrap = sharedChoiceSetInput->GetWrap();
        m_choiceSetStyle =
            static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ChoiceSetStyle>(sharedChoiceSetInput->GetChoiceSetStyle());
        RETURN_IF_FAILED(UTF8ToHString(sharedChoiceSetInput->GetValue(), m_value.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedChoiceSetInput->GetPlaceholder(), m_placeholder.GetAddressOf()));

        InitializeBaseElement(std::static_pointer_cast<BaseInputElement>(sharedChoiceSetInput));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveChoiceSetInput::get_IsMultiSelect(_Out_ boolean* isMultiSelect)
    {
        *isMultiSelect = m_isMultiSelect;
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInput::put_IsMultiSelect(boolean isMultiSelect)
    {
        m_isMultiSelect = isMultiSelect;
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInput::get_Placeholder(_Outptr_ HSTRING* placeholder)
    {
        return m_placeholder.CopyTo(placeholder);
    }

    HRESULT AdaptiveChoiceSetInput::put_Placeholder(_In_ HSTRING placeholder) { return m_placeholder.Set(placeholder); }

    HRESULT AdaptiveChoiceSetInput::get_Wrap(_Out_ boolean* wrap)
    {
        *wrap = m_wrap;
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInput::put_Wrap(boolean wrap)
    {
        m_wrap = wrap;
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInput::get_ChoiceSetStyle(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ChoiceSetStyle* choiceSetStyle)
    {
        *choiceSetStyle = m_choiceSetStyle;
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInput::put_ChoiceSetStyle(ABI::AdaptiveCards::ObjectModel::Uwp::ChoiceSetStyle choiceSetStyle)
    {
        m_choiceSetStyle = choiceSetStyle;
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInput::get_Choices(_COM_Outptr_ IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveChoiceInput*>** choices)
    {
        return m_choices.CopyTo(choices);
    }

    HRESULT AdaptiveChoiceSetInput::get_Value(_Outptr_ HSTRING* value)
    {
        m_value.CopyTo(value);
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInput::put_Value(_In_ HSTRING value)
    {
        m_value.Set(value);
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInput::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::ChoiceSetInput;
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInput::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::ChoiceSetInput> choiceSet = std::make_shared<AdaptiveCards::ChoiceSetInput>();

        RETURN_IF_FAILED(CopySharedElementProperties(*choiceSet));

        choiceSet->SetChoiceSetStyle(static_cast<AdaptiveCards::ChoiceSetStyle>(m_choiceSetStyle));
        choiceSet->SetIsMultiSelect(m_isMultiSelect);
        choiceSet->SetValue(HStringToUTF8(m_value.Get()));
        choiceSet->SetWrap(m_wrap);
        choiceSet->SetPlaceholder(HStringToUTF8(m_placeholder.Get()));

        RETURN_IF_FAILED(GenerateSharedChoices(m_choices.Get(), choiceSet->GetChoices()));

        sharedModel = std::move(choiceSet);
        return S_OK;
    }
    CATCH_RETURN;
}
