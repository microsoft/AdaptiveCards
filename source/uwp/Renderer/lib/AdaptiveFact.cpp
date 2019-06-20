// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveFact.h"
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
    HRESULT AdaptiveFact::RuntimeClassInitialize() noexcept try
    {
        RuntimeClassInitialize(std::make_shared<Fact>());
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveFact::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Fact>& sharedFact)
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedFact->GetTitle(), m_title.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedFact->GetValue(), m_value.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedFact->GetLanguage(), m_language.GetAddressOf()));
        return S_OK;
    }

    HRESULT AdaptiveFact::get_Title(_Outptr_ HSTRING* title) { return m_title.CopyTo(title); }

    HRESULT AdaptiveFact::put_Title(_In_ HSTRING title) { return m_title.Set(title); }

    HRESULT AdaptiveFact::get_Value(_Outptr_ HSTRING* value) { return m_value.CopyTo(value); }

    HRESULT AdaptiveFact::put_Value(_In_ HSTRING value) { return m_value.Set(value); }

    HRESULT AdaptiveFact::get_Language(_Outptr_ HSTRING* language) { return m_language.CopyTo(language); }

    HRESULT AdaptiveFact::put_Language(_In_ HSTRING language) { return m_language.Set(language); }

    HRESULT AdaptiveFact::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::Fact;
        return S_OK;
    }

    HRESULT AdaptiveFact::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::Fact>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::Fact> fact = std::make_shared<AdaptiveSharedNamespace::Fact>();

        std::string title;
        RETURN_IF_FAILED(HStringToUTF8(m_title.Get(), title));
        fact->SetTitle(title);

        std::string value;
        RETURN_IF_FAILED(HStringToUTF8(m_value.Get(), value));
        fact->SetValue(value);

        if (!(WindowsIsStringEmpty(m_language.Get())))
        {
            std::string language;
            RETURN_IF_FAILED(HStringToUTF8(m_language.Get(), language));
            fact->SetLanguage(language);
        }

        sharedModel = fact;
        return S_OK;
    }
    CATCH_RETURN;
}
