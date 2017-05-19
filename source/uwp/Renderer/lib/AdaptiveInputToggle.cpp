#include "pch.h"
#include "AdaptiveInputToggle.h"
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
    HRESULT AdaptiveInputToggle::RuntimeClassInitialize() noexcept try
    {
        m_sharedInputToggle = std::make_shared<InputToggle>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveInputToggle::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::InputToggle>& sharedInputToggle)
    {
        m_sharedInputToggle = sharedInputToggle;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputToggle::get_Title(HSTRING* title)
    {
        return UTF8ToHString(m_sharedInputToggle->GetTitle(), title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputToggle::put_Title(HSTRING title)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(title, out));
        m_sharedInputToggle->SetTitle(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputToggle::get_Value(HSTRING* value)
    {
        return UTF8ToHString(m_sharedInputToggle->GetValue(), value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputToggle::put_Value(HSTRING value)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(value, out));
        m_sharedInputToggle->SetValue(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputToggle::get_ValueOff(HSTRING* valueOff)
    {
        return UTF8ToHString(m_sharedInputToggle->GetValueOff(), valueOff);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputToggle::put_ValueOff(HSTRING valueOff)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(valueOff, out));
        m_sharedInputToggle->SetValueOff(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputToggle::get_ValueOn(HSTRING* valueOn)
    {
        return UTF8ToHString(m_sharedInputToggle->GetValueOn(), valueOn);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputToggle::put_ValueOn(HSTRING valueOn)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(valueOn, out));
        m_sharedInputToggle->SetValueOn(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputToggle::get_Id(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedInputToggle->GetId(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputToggle::put_Id(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedInputToggle->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputToggle::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::InputToggle;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputToggle::get_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation)
    {
        *separation = static_cast<ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle>(m_sharedInputToggle->GetSeparationStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputToggle::put_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation)
    {
        m_sharedInputToggle->SetSeparationStyle(static_cast<AdaptiveCards::SeparationStyle>(separation));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputToggle::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedInputToggle->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputToggle::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedInputToggle->SetSpeak(out);
        return S_OK;
    }

}}
