// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveNumberInput.h"

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
    HRESULT AdaptiveNumberInput::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::NumberInput> numberInput =
            std::make_shared<AdaptiveSharedNamespace::NumberInput>();
        return RuntimeClassInitialize(numberInput);
    }
    CATCH_RETURN;

    HRESULT AdaptiveNumberInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::NumberInput>& sharedNumberInput) try
    {
        if (sharedNumberInput == nullptr)
        {
            return E_INVALIDARG;
        }

        m_min = sharedNumberInput->GetMin();
        m_max = sharedNumberInput->GetMax();
        m_value = sharedNumberInput->GetValue();
        RETURN_IF_FAILED(UTF8ToHString(sharedNumberInput->GetPlaceholder(), m_placeholder.GetAddressOf()));

        InitializeBaseElement(std::static_pointer_cast<BaseInputElement>(sharedNumberInput));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveNumberInput::get_Placeholder(_Outptr_ HSTRING* placeholder)
    {
        return m_placeholder.CopyTo(placeholder);
    }

    HRESULT AdaptiveNumberInput::put_Placeholder(_In_ HSTRING placeholder) { return m_placeholder.Set(placeholder); }

    HRESULT AdaptiveNumberInput::get_Value(_Out_ INT32* value)
    {
        *value = m_value;
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::put_Value(INT32 value)
    {
        m_value = value;
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::get_Max(_Out_ INT32* max)
    {
        *max = m_max;
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::put_Max(INT32 max)
    {
        m_max = max;
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::get_Min(_Out_ INT32* min)
    {
        *min = m_min;
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::put_Min(INT32 min)
    {
        m_min = min;
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::NumberInput;
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::NumberInput> numberInput =
            std::make_shared<AdaptiveSharedNamespace::NumberInput>();

        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseInputElement>(numberInput)));

        numberInput->SetMin(m_min);
        numberInput->SetMax(m_max);
        numberInput->SetValue(m_value);
        numberInput->SetPlaceholder(HStringToUTF8(m_placeholder.Get()));

        sharedModel = numberInput;
        return S_OK;
    }
    CATCH_RETURN;
}
