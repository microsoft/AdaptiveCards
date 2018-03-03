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
    HRESULT AdaptiveTextInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TextInput>& sharedTextInput)
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

        m_isRequired = sharedTextInput->GetIsRequired();
        m_spacing = static_cast<ABI::AdaptiveCards::Rendering::Uwp::Spacing>(sharedTextInput->GetSpacing());
        m_separator = sharedTextInput->GetSeparator();
        RETURN_IF_FAILED(UTF8ToHString(sharedTextInput->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedTextInput->GetAdditionalProperties(), &m_additionalProperties));

        return S_OK;
    }

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
    HRESULT AdaptiveTextInput::get_Id(HSTRING* id)
    {
        return m_id.CopyTo(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_Id(HSTRING id)
    {
        return m_id.Set(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::TextInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_Separator(boolean* separator)
    {
        *separator = m_separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_Separator(boolean separator)
    {
        m_separator = separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_isRequired;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_IsRequired(boolean isRequired)
    {
        m_isRequired = isRequired;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveCards::TextInput> sharedTextInput = std::make_shared<AdaptiveCards::TextInput>();
        GetSharedModel(sharedTextInput);

        return StringToJsonObject(sharedTextInput->Serialize(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInput::GetSharedModel(std::shared_ptr<AdaptiveCards::TextInput>& sharedModel) try
    {
        std::shared_ptr<AdaptiveCards::TextInput> textInput = std::make_shared<AdaptiveCards::TextInput>();

        RETURN_IF_FAILED(SetSharedElementProperties(this, std::dynamic_pointer_cast<AdaptiveCards::BaseCardElement>(textInput)));
        textInput->SetIsRequired(m_isRequired);
        
        textInput->SetMaxLength(m_maxLength);
        textInput->SetIsMultiline(m_isMultiline);
        textInput->SetTextInputStyle(static_cast<AdaptiveCards::TextInputStyle>(m_textInputStyle));

        std::string placeholder;
        RETURN_IF_FAILED(HStringToUTF8(m_placeholder.Get(), placeholder));
        textInput->SetPlaceholder(placeholder);

        std::string value;
        RETURN_IF_FAILED(HStringToUTF8(m_value.Get(), value));
        textInput->SetValue(value);

        return S_OK;
    }CATCH_RETURN;
}}}
