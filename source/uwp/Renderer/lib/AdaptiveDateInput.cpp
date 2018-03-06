#include "pch.h"
#include "AdaptiveDateInput.h"
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
    HRESULT AdaptiveDateInput::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveCards::DateInput> dateInput = std::make_shared<AdaptiveCards::DateInput>();
        return RuntimeClassInitialize(dateInput);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::DateInput>& sharedDateInput) try
    {
        if (sharedDateInput == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedDateInput->GetMax(), m_max.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedDateInput->GetMin(), m_min.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedDateInput->GetPlaceholder(), m_placeholder.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedDateInput->GetValue(), m_value.GetAddressOf()));

        m_isRequired = sharedDateInput->GetIsRequired();
        m_spacing = static_cast<ABI::AdaptiveCards::Rendering::Uwp::Spacing>(sharedDateInput->GetSpacing());
        m_separator = sharedDateInput->GetSeparator();
        RETURN_IF_FAILED(UTF8ToHString(sharedDateInput->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedDateInput->GetAdditionalProperties(), &m_additionalProperties));

        return S_OK;
    }CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Max(HSTRING* max)
    {
        return m_max.CopyTo(max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Max(HSTRING max)
    {
        return m_max.Set(max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Min(HSTRING* min)
    {
        return m_min.CopyTo(min);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Min(HSTRING min)
    {
        return m_min.Set(min);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Placeholder(HSTRING* placeholder)
    {
        return m_placeholder.CopyTo(placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Placeholder(HSTRING placeholder)
    {
        return m_placeholder.Set(placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Value(HSTRING* value)
    {
        return m_value.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Value(HSTRING value)
    {
        return m_value.Set(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Id(HSTRING* id)
    {
        return m_id.CopyTo(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Id(HSTRING id)
    {
        return m_id.Set(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::DateInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Separator(boolean* separator)
    {
        *separator = m_separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Separator(boolean separator)
    {
        m_separator = separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_isRequired;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_IsRequired(boolean isRequired)
    {
        m_isRequired = isRequired;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveCards::DateInput> sharedDateInput = std::make_shared<AdaptiveCards::DateInput>();
        GetSharedModel(sharedDateInput);

        return StringToJsonObject(sharedDateInput->Serialize(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::GetSharedModel(std::shared_ptr<AdaptiveCards::DateInput>& sharedModel) try
    { 
        std::shared_ptr<AdaptiveCards::DateInput> dateInput = std::make_shared<AdaptiveCards::DateInput>();

        RETURN_IF_FAILED(SetSharedElementProperties(this, std::dynamic_pointer_cast<AdaptiveCards::BaseCardElement>(dateInput)));
        dateInput->SetIsRequired(m_isRequired);

        std::string max;
        RETURN_IF_FAILED(HStringToUTF8(m_max.Get(), max));
        dateInput->SetMax(max);

        std::string min;
        RETURN_IF_FAILED(HStringToUTF8(m_min.Get(), min));
        dateInput->SetMin(min);

        std::string placeholder;
        RETURN_IF_FAILED(HStringToUTF8(m_placeholder.Get(), placeholder));
        dateInput->SetPlaceholder(placeholder);

        std::string value;
        RETURN_IF_FAILED(HStringToUTF8(m_value.Get(), value));
        dateInput->SetValue(value);

        return S_OK;
    }CATCH_RETURN;
}}}
