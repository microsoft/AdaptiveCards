#include "pch.h"
#include "AdaptiveToggleInput.h"

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
    HRESULT AdaptiveToggleInput::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveCards::ToggleInput> toggleInput = std::make_shared<AdaptiveCards::ToggleInput>();
        return RuntimeClassInitialize(toggleInput);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ToggleInput>& sharedToggleInput) try
    {
        if (sharedToggleInput == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetTitle(), m_title.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetValue(), m_value.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetValueOn(), m_valueOn.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetValueOff(), m_valueOff.GetAddressOf()));

        m_isRequired = sharedToggleInput->GetIsRequired();
        m_spacing = static_cast<ABI::AdaptiveCards::Rendering::Uwp::Spacing>(sharedToggleInput->GetSpacing());
        m_separator = sharedToggleInput->GetSeparator();
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleInput->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedToggleInput->GetAdditionalProperties(), &m_additionalProperties));
        return S_OK;
    }CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Title(HSTRING* title)
    {
        return m_title.CopyTo(title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Title(HSTRING title)
    {
        return m_title.Set(title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Value(HSTRING* value)
    {
        return m_value.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Value(HSTRING value)
    {
        return m_value.Set(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_ValueOff(HSTRING* valueOff)
    {
        return m_valueOff.CopyTo(valueOff);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_ValueOff(HSTRING valueOff)
    {
        return m_valueOff.Set(valueOff);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_ValueOn(HSTRING* valueOn)
    {
        return m_valueOn.CopyTo(valueOn);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_ValueOn(HSTRING valueOn)
    {
        return m_valueOn.Set(valueOn);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Id(HSTRING* id)
    {
        return m_id.CopyTo(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Id(HSTRING id)
    {
        return m_id.Set(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ToggleInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_Separator(boolean* separator)
    {
        *separator = m_separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_Separator(boolean separator)
    {
        m_separator = separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_isRequired;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_IsRequired(boolean isRequired)
    {
        m_isRequired = isRequired;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveCards::ToggleInput> sharedToggleInput = std::make_shared<AdaptiveCards::ToggleInput>();
        GetSharedModel(sharedToggleInput);

        return StringToJsonObject(sharedToggleInput->Serialize(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInput::GetSharedModel(std::shared_ptr<AdaptiveCards::ToggleInput>& sharedModel) try
    {
        std::shared_ptr<AdaptiveCards::ToggleInput> toggleInput = std::make_shared<AdaptiveCards::ToggleInput>();

        RETURN_IF_FAILED(SetSharedElementProperties(this, std::dynamic_pointer_cast<AdaptiveCards::BaseCardElement>(toggleInput)));
        toggleInput->SetIsRequired(m_isRequired);

        std::string title;
        RETURN_IF_FAILED(HStringToUTF8(m_title.Get(), title));
        toggleInput->SetTitle(title);

        std::string value;
        RETURN_IF_FAILED(HStringToUTF8(m_value.Get(), value));
        toggleInput->SetValue(value);

        std::string valueOn;
        RETURN_IF_FAILED(HStringToUTF8(m_valueOn.Get(), valueOn));
        toggleInput->SetValueOn(valueOn);

        std::string valueOff;
        RETURN_IF_FAILED(HStringToUTF8(m_valueOff.Get(), valueOff));
        toggleInput->SetValueOff(valueOff);

        return S_OK;
    }CATCH_RETURN;
}}}
