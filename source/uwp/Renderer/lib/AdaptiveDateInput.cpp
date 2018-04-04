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

AdaptiveNamespaceStart
    HRESULT AdaptiveDateInput::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::DateInput> dateInput = std::make_shared<AdaptiveSharedNamespace::DateInput>();
        return RuntimeClassInitialize(dateInput);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::DateInput>& sharedDateInput) try
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
    }CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Max(HSTRING* max)
    {
        return m_max.CopyTo(max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Max(HSTRING max)
    {
        return m_max.Set(max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Min(HSTRING* min)
    {
        return m_min.CopyTo(min);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Min(HSTRING min)
    {
        return m_min.Set(min);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Placeholder(HSTRING* placeholder)
    {
        return m_placeholder.CopyTo(placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Placeholder(HSTRING placeholder)
    {
        return m_placeholder.Set(placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Value(HSTRING* value)
    {
        return m_value.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Value(HSTRING value)
    {
        return m_value.Set(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::DateInput;
        return S_OK;
    }

    HRESULT AdaptiveDateInput::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel) try
    { 
        std::shared_ptr<AdaptiveSharedNamespace::DateInput> dateInput = std::make_shared<AdaptiveSharedNamespace::DateInput>();

        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseInputElement>(dateInput)));

        std::string max;
        RETURN_IF_FAILED(HStringToUTF8(m_max.Get(), max));
        dateInput->SetMax(max);

        std::string min;
        RETURN_IF_FAILED(HStringToUTF8(m_min.Get(), min));
        dateInput->SetMin(min);

        std::string placeholder;
        RETURN_IF_FAILED(HStringToUTF8(m_placeholder.Get(), placeholder));
        dateInput->SetPlaceholder(placeholder);

        std::string value;
        RETURN_IF_FAILED(HStringToUTF8(m_value.Get(), value));
        dateInput->SetValue(value);

        sharedModel = dateInput;

        return S_OK;
    }CATCH_RETURN;
AdaptiveNamespaceEnd
