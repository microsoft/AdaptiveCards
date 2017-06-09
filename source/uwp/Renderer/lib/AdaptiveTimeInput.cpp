#include "pch.h"
#include "AdaptiveTimeInput.h"
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
    HRESULT AdaptiveTimeInput::RuntimeClassInitialize() noexcept try
    {
        m_sharedTimeInput = std::make_shared<TimeInput>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TimeInput>& sharedTimeInput)
    {
        m_sharedTimeInput = sharedTimeInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Max(HSTRING* max)
    {
        return UTF8ToHString(m_sharedTimeInput->GetMax(), max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Max(HSTRING max)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(max, out));
        m_sharedTimeInput->SetMax(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveTimeInput::get_Min(HSTRING* min)
    {
        return UTF8ToHString(m_sharedTimeInput->GetMin(), min);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveTimeInput::put_Min(HSTRING min)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(min, out));
        m_sharedTimeInput->SetMin(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveTimeInput::get_Placeholder(HSTRING* placeholder)
    {
        return UTF8ToHString(m_sharedTimeInput->GetPlaceholder(), placeholder);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveTimeInput::put_Placeholder(HSTRING placeholder)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(placeholder, out));
        m_sharedTimeInput->SetPlaceholder(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Value(HSTRING* value)
    {
        return UTF8ToHString(m_sharedTimeInput->GetValue(), value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Value(HSTRING value)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(value, out));
        m_sharedTimeInput->SetValue(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedTimeInput->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedTimeInput->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::TimeInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation)
    {
        *separation = static_cast<ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle>(m_sharedTimeInput->GetSeparationStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation)
    {
        m_sharedTimeInput->SetSeparationStyle(static_cast<AdaptiveCards::SeparationStyle>(separation));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedTimeInput->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedTimeInput->SetSpeak(out);
        return S_OK;
    }

}}
