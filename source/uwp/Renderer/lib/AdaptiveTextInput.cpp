#include "pch.h"
#include "AdaptiveTextInput.h"

#include "Util.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    HRESULT AdaptiveTextInput::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveCards::TextInput> textInput = std::make_shared<AdaptiveCards::TextInput>();
        return RuntimeClassInitialize(textInput);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TextInput>& sharedTextInput) try
    {
        if (sharedTextInput == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedTextInput->GetPlaceholder(), m_placeholder.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedTextInput->GetValue(), m_value.GetAddressOf()));
        m_maxLength = sharedTextInput->GetMaxLength();
        m_isMultiline = sharedTextInput->GetIsMultiline();
        m_textInputStyle = static_cast<ABI::AdaptiveCards::Rendering::Uwp::TextInputStyle>(sharedTextInput->GetTextInputStyle());

        InitializeBaseElement(std::static_pointer_cast<BaseInputElement>(sharedTextInput));

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_Placeholder(HSTRING* placeholder)
    {
        return m_placeholder.CopyTo(placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_Placeholder(HSTRING placeholder)
    {
        return m_placeholder.Set(placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_Value(HSTRING* value)
    {
        return m_value.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_Value(HSTRING value)
    {
        return m_value.Set(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_IsMultiline(boolean* isMultiline)
    {
        *isMultiline = m_isMultiline;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_IsMultiline(boolean isMultiline)
    {
        m_isMultiline = isMultiline;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_MaxLength(UINT32* maxLength)
    {
        *maxLength = m_maxLength;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_MaxLength(UINT32 maxLength)
    {
        m_maxLength = maxLength;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveTextInput::get_TextInputStyle(ABI::AdaptiveCards::Rendering::Uwp::TextInputStyle * textInputStyle)
    {
        *textInputStyle = m_textInputStyle;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveTextInput::put_TextInputStyle(ABI::AdaptiveCards::Rendering::Uwp::TextInputStyle textInputStyle)
    {
        m_textInputStyle = textInputStyle;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::TextInput;
        return S_OK;
    }

    HRESULT AdaptiveTextInput::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveCards::TextInput> textInput = std::make_shared<AdaptiveCards::TextInput>();

        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveCards::BaseInputElement>(textInput)));
        
        textInput->SetMaxLength(m_maxLength);
        textInput->SetIsMultiline(m_isMultiline);
        textInput->SetTextInputStyle(static_cast<AdaptiveCards::TextInputStyle>(m_textInputStyle));

        std::string placeholder;
        RETURN_IF_FAILED(HStringToUTF8(m_placeholder.Get(), placeholder));
        textInput->SetPlaceholder(placeholder);

        std::string value;
        RETURN_IF_FAILED(HStringToUTF8(m_value.Get(), value));
        textInput->SetValue(value);

        sharedModel = textInput;

        return S_OK;
    }CATCH_RETURN;
}}}
