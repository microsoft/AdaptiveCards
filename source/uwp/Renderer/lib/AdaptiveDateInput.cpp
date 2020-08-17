// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveDateInput.h"
#include "Util.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveDateInput::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::DateInput> dateInput = std::make_shared<AdaptiveSharedNamespace::DateInput>();
        return RuntimeClassInitialize(dateInput);
    }
    CATCH_RETURN;

    HRESULT AdaptiveDateInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::DateInput>& sharedDateInput)
    try
    {
        if (sharedDateInput == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedDateInput->GetMax(), m_max.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedDateInput->GetMin(), m_min.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedDateInput->GetPlaceholder(), m_placeholder.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedDateInput->GetValue(), m_value.GetAddressOf()));

        InitializeBaseElement(std::static_pointer_cast<BaseInputElement>(sharedDateInput));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveDateInput::get_Max(_Outptr_ HSTRING* max) { return m_max.CopyTo(max); }

    HRESULT AdaptiveDateInput::put_Max(_In_ HSTRING max) { return m_max.Set(max); }

    HRESULT AdaptiveDateInput::get_Min(_Outptr_ HSTRING* min) { return m_min.CopyTo(min); }

    HRESULT AdaptiveDateInput::put_Min(_In_ HSTRING min) { return m_min.Set(min); }

    HRESULT AdaptiveDateInput::get_Placeholder(_Outptr_ HSTRING* placeholder)
    {
        return m_placeholder.CopyTo(placeholder);
    }

    HRESULT AdaptiveDateInput::put_Placeholder(_In_ HSTRING placeholder) { return m_placeholder.Set(placeholder); }

    HRESULT AdaptiveDateInput::get_Value(_Outptr_ HSTRING* value) { return m_value.CopyTo(value); }

    HRESULT AdaptiveDateInput::put_Value(_In_ HSTRING value) { return m_value.Set(value); }

    HRESULT AdaptiveDateInput::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::DateInput;
        return S_OK;
    }

    HRESULT AdaptiveDateInput::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::DateInput> dateInput = std::make_shared<AdaptiveSharedNamespace::DateInput>();
        RETURN_IF_FAILED(CopySharedElementProperties(*dateInput));

        dateInput->SetMax(HStringToUTF8(m_max.Get()));
        dateInput->SetMin(HStringToUTF8(m_min.Get()));
        dateInput->SetPlaceholder(HStringToUTF8(m_placeholder.Get()));
        dateInput->SetValue(HStringToUTF8(m_value.Get()));

        sharedModel = std::move(dateInput);

        return S_OK;
    }
    CATCH_RETURN;
}
