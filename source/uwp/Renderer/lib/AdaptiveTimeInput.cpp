#include "pch.h"
#include "AdaptiveTimeInput.h"

#include "Util.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

AdaptiveNamespaceStart
    HRESULT AdaptiveTimeInput::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::TimeInput> timeInput = std::make_shared<AdaptiveSharedNamespace::TimeInput>();
        return RuntimeClassInitialize(timeInput);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::TimeInput>& sharedTimeInput) try
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
    }CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Max(HSTRING* max)
    {
        return m_max.CopyTo(max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Max(HSTRING max)
    {
        return m_max.Set(max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Min(HSTRING* min)
    {
        return m_min.CopyTo(min);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Min(HSTRING min)
    {
        return m_min.Set(min);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Placeholder(HSTRING* placeholder)
    {
        return m_placeholder.CopyTo(placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Placeholder(HSTRING placeholder)
    {
        return m_placeholder.Set(placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Value(HSTRING* value)
    {
        return m_value.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Value(HSTRING value)
    {
        return m_value.Set(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::TimeInput;
        return S_OK;
    }

    HRESULT AdaptiveTimeInput::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::TimeInput> timeInput = std::make_shared<AdaptiveSharedNamespace::TimeInput>();

        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseInputElement>(timeInput)));

        std::string max;
        RETURN_IF_FAILED(HStringToUTF8(m_max.Get(), max));
        timeInput->SetMax(max);

        std::string min;
        RETURN_IF_FAILED(HStringToUTF8(m_min.Get(), min));
        timeInput->SetMin(min);

        std::string placeholder;
        RETURN_IF_FAILED(HStringToUTF8(m_placeholder.Get(), placeholder));
        timeInput->SetPlaceholder(placeholder);

        std::string value;
        RETURN_IF_FAILED(HStringToUTF8(m_value.Get(), value));
        timeInput->SetValue(value);

        sharedModel = timeInput;

        return S_OK;
    }CATCH_RETURN;
AdaptiveNamespaceEnd
