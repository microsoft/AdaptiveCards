// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveNumberInput.h"

#include <winrt/Windows.Foundation.h>

using namespace ABI::AdaptiveCards::ObjectModel::Uwp;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveNumberInput::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::NumberInput> numberInput = std::make_shared<AdaptiveCards::NumberInput>();
        return RuntimeClassInitialize(numberInput);
    }
    CATCH_RETURN;

    HRESULT AdaptiveNumberInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::NumberInput>& sharedNumberInput)
    try
    {
        if (sharedNumberInput == nullptr)
        {
            return E_INVALIDARG;
        }

        const auto sharedMin = sharedNumberInput->GetMin();
        if (sharedMin)
        {
            m_min = winrt::box_value(sharedMin.value()).as<ABI::Windows::Foundation::IReference<double>>();
        }

        const auto sharedMax = sharedNumberInput->GetMax();
        if (sharedMax)
        {
            m_max = winrt::box_value(sharedMax.value()).as<ABI::Windows::Foundation::IReference<double>>();
        }

        const auto sharedValue = sharedNumberInput->GetValue();
        if (sharedValue)
        {
            m_value = winrt::box_value(sharedValue.value()).as<ABI::Windows::Foundation::IReference<double>>();
        }

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

    HRESULT AdaptiveNumberInput::get_Value(_Out_ ABI::Windows::Foundation::IReference<double>** value)
    {
        m_value.copy_to(value);
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::put_Value(ABI::Windows::Foundation::IReference<double>* value)
    {
        m_value.copy_from(value);
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::get_Max(_Out_ ABI::Windows::Foundation::IReference<double>** max)
    {
        m_max.copy_to(max);
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::put_Max(ABI::Windows::Foundation::IReference<double>* max)
    {
        m_max.copy_from(max);
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::get_Min(_Out_ ABI::Windows::Foundation::IReference<double>** min)
    {
        m_min.copy_to(min);
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::put_Min(ABI::Windows::Foundation::IReference<double>* min)
    {
        m_min.copy_from(min);
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::NumberInput;
        return S_OK;
    }

    HRESULT AdaptiveNumberInput::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::NumberInput> numberInput = std::make_shared<AdaptiveCards::NumberInput>();

        RETURN_IF_FAILED(CopySharedElementProperties(*numberInput));

        std::optional<double> min;
        if (m_min)
        {
            double minValue;
            RETURN_IF_FAILED(m_min->get_Value(&minValue));
            min = minValue;
        }
        numberInput->SetMin(min);

        std::optional<double> max;
        if (m_max)
        {
            double maxValue;
            RETURN_IF_FAILED(m_max->get_Value(&maxValue));
            max = maxValue;
        }
        numberInput->SetMax(max);

        std::optional<double> value;
        if (m_value)
        {
            double valueValue;
            RETURN_IF_FAILED(m_value->get_Value(&valueValue));
            value = valueValue;
        }
        numberInput->SetValue(value);

        numberInput->SetPlaceholder(HStringToUTF8(m_placeholder.Get()));

        sharedModel = std::move(numberInput);
        return S_OK;
    }
    CATCH_RETURN;
}
