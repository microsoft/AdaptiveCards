#include "pch.h"
#include "AdaptiveNumberInput.h"
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
    HRESULT AdaptiveNumberInput::RuntimeClassInitialize() noexcept try
    {
        m_sharedNumberInput = std::make_shared<NumberInput>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::NumberInput>& sharedNumberInput)
    {
        m_sharedNumberInput = sharedNumberInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Placeholder(HSTRING* placeholder)
    {
        return UTF8ToHString(m_sharedNumberInput->GetPlaceholder(), placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Placeholder(HSTRING placeholder)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(placeholder, out));
        m_sharedNumberInput->SetPlaceholder(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Value(INT32* value)
    {
        *value = m_sharedNumberInput->GetValue();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Value(INT32 value)
    {
        m_sharedNumberInput->SetValue(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Max(INT32* max)
    {
        *max = m_sharedNumberInput->GetMax();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Max(INT32 max)
    {
        m_sharedNumberInput->SetMax(max);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Min(INT32* min)
    {
        *min = m_sharedNumberInput->GetMin();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Min(INT32 min)
    {
        m_sharedNumberInput->SetMin(min);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedNumberInput->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedNumberInput->SetId(out);
        return S_OK;
    }
    
    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::NumberInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation)
    {
        *separation = static_cast<ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle>(m_sharedNumberInput->GetSeparationStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation)
    {
        m_sharedNumberInput->SetSeparationStyle(static_cast<AdaptiveCards::SeparationStyle>(separation));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedNumberInput->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedNumberInput->SetSpeak(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_sharedNumberInput->GetIsRequired();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_IsRequired(boolean isRequired)
    {
        m_sharedNumberInput->SetIsRequired(isRequired);
        return S_OK;
    }

}}
