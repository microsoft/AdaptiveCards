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

AdaptiveNamespaceStart
    HRESULT AdaptiveFact::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveFact::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Fact>& sharedFact)
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedFact->GetTitle(), m_title.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedFact->GetValue(), m_value.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedFact->GetLanguage(), m_language.GetAddressOf()));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFact::get_Title(HSTRING* title)
    {
        return m_title.CopyTo(title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFact::put_Title(HSTRING title)
    {
        return m_title.Set(title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFact::get_Value(HSTRING* value)
    {
        return m_value.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFact::put_Value(HSTRING value)
    {
        return m_value.Set(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFact::get_Language(HSTRING* language)
    {
        return m_language.CopyTo(language);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFact::put_Language(HSTRING language)
    {
        return m_language.Set(language);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFact::get_ElementType(ElementType* elementType)
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

        std::string language;
        if (!(WindowsIsStringEmpty(m_language.Get())))
        {
            RETURN_IF_FAILED(HStringToUTF8(m_language.Get(), language));
            fact->SetLanguage(language);
        }

        sharedModel = fact;
        return S_OK;
    } CATCH_RETURN;
AdaptiveNamespaceEnd
