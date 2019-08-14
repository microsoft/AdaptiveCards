// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveChoiceInput.h"
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
    HRESULT AdaptiveChoiceInput::RuntimeClassInitialize() noexcept try
    {
        m_sharedChoiceInput = std::make_shared<ChoiceInput>();
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveChoiceInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput>& sharedChoiceInput)
    {
        m_sharedChoiceInput = sharedChoiceInput;
        return S_OK;
    }

    HRESULT AdaptiveChoiceInput::get_Title(_Outptr_ HSTRING* title)
    {
        return UTF8ToHString(m_sharedChoiceInput->GetTitle(), title);
    }

    HRESULT AdaptiveChoiceInput::put_Title(_In_ HSTRING title)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(title, out));
        m_sharedChoiceInput->SetTitle(out);
        return S_OK;
    }

    HRESULT AdaptiveChoiceInput::get_Value(_Outptr_ HSTRING* value)
    {
        return UTF8ToHString(m_sharedChoiceInput->GetValue(), value);
    }

    HRESULT AdaptiveChoiceInput::put_Value(_In_ HSTRING value)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(value, out));
        m_sharedChoiceInput->SetValue(out);
        return S_OK;
    }

    HRESULT AdaptiveChoiceInput::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::ChoiceInput;
        return S_OK;
    }

    HRESULT AdaptiveChoiceInput::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput>& sharedModel)
    {
        sharedModel = m_sharedChoiceInput;
        return S_OK;
    }
}
