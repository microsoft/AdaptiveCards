#include "pch.h"
#include "AdaptiveInputText.h"
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
    HRESULT AdaptiveInputText::RuntimeClassInitialize() noexcept try
    {
        m_sharedInputText = std::make_shared<InputText>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveInputText::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::InputText>& sharedInputText)
    {
        m_sharedInputText = sharedInputText;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputText::get_Placeholder(HSTRING* placeholder)
    {
        return UTF8ToHString(m_sharedInputText->GetPlaceholder(), placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputText::put_Placeholder(HSTRING placeholder)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(placeholder, out));
        m_sharedInputText->SetPlaceholder(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputText::get_Value(HSTRING* value)
    {
        return UTF8ToHString(m_sharedInputText->GetValue(), value);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputText::put_Value(HSTRING value)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(value, out));
        m_sharedInputText->SetValue(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputText::get_IsMultiline(boolean* isMultiline)
    {
        *isMultiline = m_sharedInputText->GetIsMultiline();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputText::put_IsMultiline(boolean isMultiline)
    {
        m_sharedInputText->SetIsMultiline(Boolify(isMultiline));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputText::get_MaxLength(UINT32* maxLength)
    {
        *maxLength = m_sharedInputText->GetMaxLength();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputText::put_MaxLength(UINT32 maxLength)
    {
        m_sharedInputText->SetMaxLength(maxLength);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputText::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::InputText;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputText::get_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation)
    {
        *separation = static_cast<ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle>(m_sharedInputText->GetSeparationStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputText::put_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation)
    {
        m_sharedInputText->SetSeparationStyle(static_cast<AdaptiveCards::SeparationStyle>(separation));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputText::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedInputText->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputText::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedInputText->SetSpeak(out);
        return S_OK;
    }

}}
