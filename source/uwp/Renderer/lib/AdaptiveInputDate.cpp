#include "pch.h"
#include "AdaptiveInputDate.h"
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
    HRESULT AdaptiveInputDate::RuntimeClassInitialize() noexcept try
    {
        m_sharedInputDate = std::make_shared<InputDate>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveInputDate::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::InputDate>& sharedInputDate)
    {
        m_sharedInputDate = sharedInputDate;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputDate::get_Max(HSTRING* max)
    {
        return UTF8ToHString(m_sharedInputDate->GetMax(), max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputDate::put_Max(HSTRING max)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(max, out));
        m_sharedInputDate->SetMax(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputDate::get_Min(HSTRING* min)
    {
        return UTF8ToHString(m_sharedInputDate->GetMin(), min);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputDate::put_Min(HSTRING min)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(min, out));
        m_sharedInputDate->SetMin(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputDate::get_Placeholder(HSTRING* placeholder)
    {
        return UTF8ToHString(m_sharedInputDate->GetPlaceholder(), placeholder);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputDate::put_Placeholder(HSTRING placeholder)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(placeholder, out));
        m_sharedInputDate->SetPlaceholder(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputDate::get_Value(HSTRING* value)
    {
        return UTF8ToHString(m_sharedInputDate->GetValue(), value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputDate::put_Value(HSTRING value)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(value, out));
        m_sharedInputDate->SetValue(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputDate::get_Id(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedInputDate->GetId(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputDate::put_Id(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedInputDate->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputDate::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::InputDate;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputDate::get_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation)
    {
        *separation = static_cast<ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle>(m_sharedInputDate->GetSeparationStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputDate::put_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation)
    {
        m_sharedInputDate->SetSeparationStyle(static_cast<AdaptiveCards::SeparationStyle>(separation));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputDate::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedInputDate->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputDate::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedInputDate->SetSpeak(out);
        return S_OK;
    }

}}
