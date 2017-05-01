#include "pch.h"
#include "AdaptiveInputTime.h"
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
    HRESULT AdaptiveInputTime::RuntimeClassInitialize() noexcept try
    {
        m_sharedInputTime = std::make_shared<InputTime>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveInputTime::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::InputTime>& sharedInputTime)
    {
        m_sharedInputTime = sharedInputTime;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputTime::get_Max(HSTRING* max)
    {
        return UTF8ToHString(m_sharedInputTime->GetMax(), max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputTime::put_Max(HSTRING max)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(max, out));
        m_sharedInputTime->SetMax(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputTime::get_Min(HSTRING* min)
    {
        return UTF8ToHString(m_sharedInputTime->GetMin(), min);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputTime::put_Min(HSTRING min)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(min, out));
        m_sharedInputTime->SetMin(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputTime::get_Placeholder(HSTRING* placeholder)
    {
        return UTF8ToHString(m_sharedInputTime->GetPlaceholder(), placeholder);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputTime::put_Placeholder(HSTRING placeholder)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(placeholder, out));
        m_sharedInputTime->SetPlaceholder(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputTime::get_Value(HSTRING* value)
    {
        return UTF8ToHString(m_sharedInputTime->GetValue(), value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputTime::put_Value(HSTRING value)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(value, out));
        m_sharedInputTime->SetValue(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputTime::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::InputTime;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputTime::get_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation)
    {
        *separation = static_cast<ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle>(m_sharedInputTime->GetSeparationStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputTime::put_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation)
    {
        m_sharedInputTime->SetSeparationStyle(static_cast<AdaptiveCards::SeparationStyle>(separation));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputTime::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedInputTime->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputTime::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedInputTime->SetSpeak(out);
        return S_OK;
    }

}}
