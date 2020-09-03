// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveInputElement.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveInputElementBase::InitializeBaseElement(const std::shared_ptr<AdaptiveSharedNamespace::BaseInputElement>& sharedModel)
    {
        AdaptiveCardElementBase::InitializeBaseElement(std::static_pointer_cast<AdaptiveSharedNamespace::BaseCardElement>(sharedModel));
        m_isRequired = sharedModel->GetIsRequired();
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetErrorMessage(), m_errorMessage.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetLabel(), m_label.GetAddressOf()));

        return S_OK;
    }

    HRESULT AdaptiveInputElementBase::get_IsRequired(_Out_ boolean* isRequired)
    {
        *isRequired = m_isRequired;
        return S_OK;
    }

    HRESULT AdaptiveInputElementBase::put_IsRequired(boolean isRequired)
    {
        m_isRequired = isRequired;
        return S_OK;
    }

    HRESULT AdaptiveInputElementBase::get_ErrorMessage(_Outptr_ HSTRING* title) { return m_errorMessage.CopyTo(title); }

    HRESULT AdaptiveInputElementBase::put_ErrorMessage(_In_ HSTRING title) { return m_errorMessage.Set(title); }

    HRESULT AdaptiveInputElementBase::get_Label(_Outptr_ HSTRING* label) { return m_label.CopyTo(label); }

    HRESULT AdaptiveInputElementBase::put_Label(_In_ HSTRING label) { return m_label.Set(label); }

    HRESULT AdaptiveInputElementBase::CopySharedElementProperties(AdaptiveSharedNamespace::BaseInputElement& sharedCardElement)
    {
        AdaptiveCardElementBase::CopySharedElementProperties(sharedCardElement);
        sharedCardElement.SetIsRequired(m_isRequired);
        sharedCardElement.SetErrorMessage(HStringToUTF8(m_errorMessage.Get()));
        sharedCardElement.SetLabel(HStringToUTF8(m_label.Get()));
        return S_OK;
    }
}
