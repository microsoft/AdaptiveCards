#include "pch.h"
#include "AdaptiveInputChoice.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "XamlCardRendererComponent.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveInputChoice::RuntimeClassInitialize() noexcept try
    {
        m_sharedInputChoice = std::make_shared<InputChoice>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoice::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::InputChoice>& sharedInputChoice)
    {
        m_sharedInputChoice = sharedInputChoice;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoice::get_Title(HSTRING* title)
    {
        return UTF8ToHString(m_sharedInputChoice->GetTitle(), title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoice::put_Title(HSTRING title)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(title, out));
        m_sharedInputChoice->SetTitle(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoice::get_Value(HSTRING* value)
    {
        return UTF8ToHString(m_sharedInputChoice->GetValue(), value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoice::put_Value(HSTRING value)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(value, out));
        m_sharedInputChoice->SetValue(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoice::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedInputChoice->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoice::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedInputChoice->SetSpeak(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoice::get_IsSelected(boolean * isSelected)
    {
        *isSelected = m_sharedInputChoice->GetIsSelected();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoice::put_IsSelected(boolean isSelected)
    {
        m_sharedInputChoice->SetIsSelected(isSelected);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoice::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::InputChoice;
        return S_OK;
    }

}}
