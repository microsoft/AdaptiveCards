#include "pch.h"
#include "AdaptiveToggleInput.h"

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
    HRESULT AdaptiveToggleInput::RuntimeClassInitialize() noexcept try
    {
        m_sharedToggleInput = std::make_shared<ToggleInput>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ToggleInput>& sharedToggleInput)
    {
        m_sharedToggleInput = sharedToggleInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Title(HSTRING* title)
    {
        return UTF8ToHString(m_sharedToggleInput->GetTitle(), title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Title(HSTRING title)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(title, out));
        m_sharedToggleInput->SetTitle(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Value(HSTRING* value)
    {
        return UTF8ToHString(m_sharedToggleInput->GetValue(), value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Value(HSTRING value)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(value, out));
        m_sharedToggleInput->SetValue(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveToggleInput::get_ValueOff(HSTRING* valueOff)
    {
        return UTF8ToHString(m_sharedToggleInput->GetValueOff(), valueOff);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveToggleInput::put_ValueOff(HSTRING valueOff)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(valueOff, out));
        m_sharedToggleInput->SetValueOff(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveToggleInput::get_ValueOn(HSTRING* valueOn)
    {
        return UTF8ToHString(m_sharedToggleInput->GetValueOn(), valueOn);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveToggleInput::put_ValueOn(HSTRING valueOn)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(valueOn, out));
        m_sharedToggleInput->SetValueOn(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedToggleInput->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedToggleInput->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ToggleInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Spacing(ABI::AdaptiveCards::XamlCardRenderer::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::XamlCardRenderer::Spacing>(m_sharedToggleInput->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Spacing(ABI::AdaptiveCards::XamlCardRenderer::Spacing spacing)
    {
        m_sharedToggleInput->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Separator(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator** separator)
    {
        return GenerateSeparatorProjection(m_sharedToggleInput->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Separator(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator* separator)
    {
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedToggleInput->SetSeparator(sharedSeparator);

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedToggleInput->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedToggleInput->SetSpeak(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_sharedToggleInput->GetIsRequired();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_IsRequired(boolean isRequired)
    {
        m_sharedToggleInput->SetIsRequired(isRequired);
        return S_OK;
    }

}}
