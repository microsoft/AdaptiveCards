#include "pch.h"
#include "AdaptiveTextInput.h"

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
    HRESULT AdaptiveTextInput::RuntimeClassInitialize() noexcept try
    {
        m_sharedTextInput = std::make_shared<TextInput>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TextInput>& sharedTextInput)
    {
        m_sharedTextInput = sharedTextInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_Placeholder(HSTRING* placeholder)
    {
        return UTF8ToHString(m_sharedTextInput->GetPlaceholder(), placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_Placeholder(HSTRING placeholder)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(placeholder, out));
        m_sharedTextInput->SetPlaceholder(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveTextInput::get_Value(HSTRING* value)
    {
        return UTF8ToHString(m_sharedTextInput->GetValue(), value);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveTextInput::put_Value(HSTRING value)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(value, out));
        m_sharedTextInput->SetValue(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_IsMultiline(boolean* isMultiline)
    {
        *isMultiline = m_sharedTextInput->GetIsMultiline();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_IsMultiline(boolean isMultiline)
    {
        m_sharedTextInput->SetIsMultiline(Boolify(isMultiline));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_MaxLength(UINT32* maxLength)
    {
        *maxLength = m_sharedTextInput->GetMaxLength();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_MaxLength(UINT32 maxLength)
    {
        m_sharedTextInput->SetMaxLength(maxLength);
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveTextInput::get_TextInputStyle(ABI::AdaptiveCards::XamlCardRenderer::TextInputStyle * textInputStyle)
    {
        *textInputStyle = static_cast<ABI::AdaptiveCards::XamlCardRenderer::TextInputStyle>(m_sharedTextInput->GetTextInputStyle());
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveTextInput::put_TextInputStyle(ABI::AdaptiveCards::XamlCardRenderer::TextInputStyle textInputStyle)
    {
        m_sharedTextInput->SetTextInputStyle(static_cast<AdaptiveCards::TextInputStyle>(textInputStyle));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedTextInput->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedTextInput->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::TextInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_Spacing(ABI::AdaptiveCards::XamlCardRenderer::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::XamlCardRenderer::Spacing>(m_sharedTextInput->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_Spacing(ABI::AdaptiveCards::XamlCardRenderer::Spacing spacing)
    {
        m_sharedTextInput->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_Separator(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator** separator)
    {
        return GenerateSeparatorProjection(m_sharedTextInput->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_Separator(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator* separator)
    {
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedTextInput->SetSeparator(sharedSeparator);

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedTextInput->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedTextInput->SetSpeak(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_sharedTextInput->GetIsRequired();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_IsRequired(boolean isRequired)
    {
        m_sharedTextInput->SetIsRequired(isRequired);
        return S_OK;
    }

}}
