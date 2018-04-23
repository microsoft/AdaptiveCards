#include "pch.h"
#include "AdaptiveToggleInput.h"

#include "Util.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

AdaptiveNamespaceStart
    HRESULT AdaptiveToggleInput::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ToggleInput> toggleInput = std::make_shared<AdaptiveSharedNamespace::ToggleInput>();
        return RuntimeClassInitialize(toggleInput);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::ToggleInput>& sharedToggleInput) try
    {
        if (sharedToggleInput == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetTitle(), m_title.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetValue(), m_value.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetValueOn(), m_valueOn.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetValueOff(), m_valueOff.GetAddressOf()));

        InitializeBaseElement(std::static_pointer_cast<BaseInputElement>(sharedToggleInput));
        return S_OK;
    }CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Title(HSTRING* title)
    {
        return m_title.CopyTo(title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Title(HSTRING title)
    {
        return m_title.Set(title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Value(HSTRING* value)
    {
        return m_value.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Value(HSTRING value)
    {
        return m_value.Set(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_ValueOff(HSTRING* valueOff)
    {
        return m_valueOff.CopyTo(valueOff);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_ValueOff(HSTRING valueOff)
    {
        return m_valueOff.Set(valueOff);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_ValueOn(HSTRING* valueOn)
    {
        return m_valueOn.CopyTo(valueOn);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_ValueOn(HSTRING valueOn)
    {
        return m_valueOn.Set(valueOn);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ToggleInput;
        return S_OK;
    }

    HRESULT AdaptiveToggleInput::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ToggleInput> toggleInput = std::make_shared<AdaptiveSharedNamespace::ToggleInput>();

        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseInputElement>(toggleInput)));

        std::string title;
        RETURN_IF_FAILED(HStringToUTF8(m_title.Get(), title));
        toggleInput->SetTitle(title);

        std::string value;
        RETURN_IF_FAILED(HStringToUTF8(m_value.Get(), value));
        toggleInput->SetValue(value);

        std::string valueOn;
        RETURN_IF_FAILED(HStringToUTF8(m_valueOn.Get(), valueOn));
        toggleInput->SetValueOn(valueOn);

        std::string valueOff;
        RETURN_IF_FAILED(HStringToUTF8(m_valueOff.Get(), valueOff));
        toggleInput->SetValueOff(valueOff);

        sharedModel = toggleInput;

        return S_OK;
    }CATCH_RETURN;
AdaptiveNamespaceEnd
