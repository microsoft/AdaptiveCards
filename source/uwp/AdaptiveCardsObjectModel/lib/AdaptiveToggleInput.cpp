// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveToggleInput.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveToggleInput::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::ToggleInput> toggleInput = std::make_shared<AdaptiveCards::ToggleInput>();
        return RuntimeClassInitialize(toggleInput);
    }
    CATCH_RETURN;

    HRESULT AdaptiveToggleInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ToggleInput>& sharedToggleInput)
    try
    {
        if (sharedToggleInput == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetTitle(), m_title.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetValue(), m_value.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetValueOn(), m_valueOn.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetValueOff(), m_valueOff.GetAddressOf()));
        m_wrap = sharedToggleInput->GetWrap();

        InitializeBaseElement(std::static_pointer_cast<BaseInputElement>(sharedToggleInput));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveToggleInput::get_Title(_Outptr_ HSTRING* title) { return m_title.CopyTo(title); }

    HRESULT AdaptiveToggleInput::put_Title(_In_ HSTRING title) { return m_title.Set(title); }

    HRESULT AdaptiveToggleInput::get_Value(_Outptr_ HSTRING* value) { return m_value.CopyTo(value); }

    HRESULT AdaptiveToggleInput::put_Value(_In_ HSTRING value) { return m_value.Set(value); }

    HRESULT AdaptiveToggleInput::get_ValueOff(_Outptr_ HSTRING* valueOff) { return m_valueOff.CopyTo(valueOff); }

    HRESULT AdaptiveToggleInput::put_ValueOff(_In_ HSTRING valueOff) { return m_valueOff.Set(valueOff); }

    HRESULT AdaptiveToggleInput::get_ValueOn(_Outptr_ HSTRING* valueOn) { return m_valueOn.CopyTo(valueOn); }

    HRESULT AdaptiveToggleInput::put_ValueOn(_In_ HSTRING valueOn) { return m_valueOn.Set(valueOn); }

    HRESULT AdaptiveToggleInput::get_Wrap(_Out_ boolean* wrap)
    {
        *wrap = m_wrap;
        return S_OK;
    }

    HRESULT AdaptiveToggleInput::put_Wrap(boolean wrap)
    {
        m_wrap = wrap;
        return S_OK;
    }

    HRESULT AdaptiveToggleInput::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::ToggleInput;
        return S_OK;
    }

    HRESULT AdaptiveToggleInput::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::ToggleInput> toggleInput = std::make_shared<AdaptiveCards::ToggleInput>();

        RETURN_IF_FAILED(CopySharedElementProperties(*toggleInput));

        toggleInput->SetTitle(HStringToUTF8(m_title.Get()));
        toggleInput->SetValue(HStringToUTF8(m_value.Get()));
        toggleInput->SetValueOn(HStringToUTF8(m_valueOn.Get()));
        toggleInput->SetValueOff(HStringToUTF8(m_valueOff.Get()));
        toggleInput->SetWrap(m_wrap);

        sharedModel = std::move(toggleInput);

        return S_OK;
    }
    CATCH_RETURN;
}
