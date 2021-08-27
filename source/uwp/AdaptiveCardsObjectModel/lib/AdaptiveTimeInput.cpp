// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTimeInput.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveTimeInput::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::TimeInput> timeInput = std::make_shared<AdaptiveCards::TimeInput>();
        return RuntimeClassInitialize(timeInput);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTimeInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TimeInput>& sharedTimeInput)
    try
    {
        if (sharedTimeInput == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedTimeInput->GetMax(), m_max.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedTimeInput->GetMin(), m_min.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedTimeInput->GetPlaceholder(), m_placeholder.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedTimeInput->GetValue(), m_value.GetAddressOf()));

        InitializeBaseElement(std::static_pointer_cast<BaseInputElement>(sharedTimeInput));

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTimeInput::get_Max(_Outptr_ HSTRING* max) { return m_max.CopyTo(max); }

    HRESULT AdaptiveTimeInput::put_Max(_In_ HSTRING max) { return m_max.Set(max); }

    HRESULT AdaptiveTimeInput::get_Min(_Outptr_ HSTRING* min) { return m_min.CopyTo(min); }

    HRESULT AdaptiveTimeInput::put_Min(_In_ HSTRING min) { return m_min.Set(min); }

    HRESULT AdaptiveTimeInput::get_Placeholder(_Outptr_ HSTRING* placeholder)
    {
        return m_placeholder.CopyTo(placeholder);
    }

    HRESULT AdaptiveTimeInput::put_Placeholder(_In_ HSTRING placeholder) { return m_placeholder.Set(placeholder); }

    HRESULT AdaptiveTimeInput::get_Value(_Outptr_ HSTRING* value) { return m_value.CopyTo(value); }

    HRESULT AdaptiveTimeInput::put_Value(_In_ HSTRING value) { return m_value.Set(value); }

    HRESULT AdaptiveTimeInput::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::TimeInput;
        return S_OK;
    }

    HRESULT AdaptiveTimeInput::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::TimeInput> timeInput = std::make_shared<AdaptiveCards::TimeInput>();

        RETURN_IF_FAILED(CopySharedElementProperties(*timeInput));

        timeInput->SetMax(HStringToUTF8(m_max.Get()));
        timeInput->SetMin(HStringToUTF8(m_min.Get()));
        timeInput->SetPlaceholder(HStringToUTF8(m_placeholder.Get()));
        timeInput->SetValue(HStringToUTF8(m_value.Get()));

        sharedModel = std::move(timeInput);

        return S_OK;
    }
    CATCH_RETURN;
}
