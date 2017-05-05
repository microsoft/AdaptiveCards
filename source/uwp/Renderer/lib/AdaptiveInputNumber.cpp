#include "pch.h"
#include "AdaptiveInputNumber.h"
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
    HRESULT AdaptiveInputNumber::RuntimeClassInitialize() noexcept try
    {
        m_sharedInputNumber = std::make_shared<InputNumber>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveInputNumber::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::InputNumber>& sharedInputNumber)
    {
        m_sharedInputNumber = sharedInputNumber;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputNumber::get_Placeholder(HSTRING* placeholder)
    {
        return UTF8ToHString(m_sharedInputNumber->GetPlaceholder(), placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputNumber::put_Placeholder(HSTRING placeholder)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(placeholder, out));
        m_sharedInputNumber->SetPlaceholder(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputNumber::get_Value(HSTRING* value)
    {
        return UTF8ToHString(m_sharedInputNumber->GetValue(), value);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputNumber::put_Value(HSTRING value)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(value, out));
        m_sharedInputNumber->SetValue(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputNumber::get_Max(UINT32* max)
    {
        *max = m_sharedInputNumber->GetMax();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputNumber::put_Max(UINT32 max)
    {
        m_sharedInputNumber->SetMax(max);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputNumber::get_Min(UINT32* min)
    {
        *min = m_sharedInputNumber->GetMin();
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveInputNumber::put_Min(UINT32 min)
    {
        m_sharedInputNumber->SetMin(min);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputNumber::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::InputNumber;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputNumber::get_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation)
    {
        *separation = static_cast<ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle>(m_sharedInputNumber->GetSeparationStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputNumber::put_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation)
    {
        m_sharedInputNumber->SetSeparationStyle(static_cast<AdaptiveCards::SeparationStyle>(separation));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputNumber::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedInputNumber->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputNumber::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedInputNumber->SetSpeak(out);
        return S_OK;
    }

}}
