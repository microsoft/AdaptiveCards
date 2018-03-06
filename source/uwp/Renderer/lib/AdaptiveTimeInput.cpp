#include "pch.h"
#include "AdaptiveTimeInput.h"

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
    HRESULT AdaptiveTimeInput::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveCards::TimeInput> timeInput = std::make_shared<AdaptiveCards::TimeInput>();
        return RuntimeClassInitialize(timeInput);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TimeInput>& sharedTimeInput) try
    {
        if (sharedTimeInput == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedTimeInput->GetMax(), m_max.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedTimeInput->GetMin(), m_min.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedTimeInput->GetPlaceholder(), m_placeholder.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedTimeInput->GetValue(), m_value.GetAddressOf()));

        m_isRequired = sharedTimeInput->GetIsRequired();
        m_spacing = static_cast<ABI::AdaptiveCards::Rendering::Uwp::Spacing>(sharedTimeInput->GetSpacing());
        m_separator = sharedTimeInput->GetSeparator();
        RETURN_IF_FAILED(UTF8ToHString(sharedTimeInput->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedTimeInput->GetAdditionalProperties(), &m_additionalProperties));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedTimeInput->GetAdditionalProperties(), &m_additionalProperties));

        return S_OK;
    }CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Max(HSTRING* max)
    {
        return m_max.CopyTo(max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Max(HSTRING max)
    {
        return m_max.Set(max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Min(HSTRING* min)
    {
        return m_min.CopyTo(min);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Min(HSTRING min)
    {
        return m_min.Set(min);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Placeholder(HSTRING* placeholder)
    {
        return m_placeholder.CopyTo(placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Placeholder(HSTRING placeholder)
    {
        return m_placeholder.Set(placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Value(HSTRING* value)
    {
        return m_value.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Value(HSTRING value)
    {
        return m_value.Set(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Id(HSTRING* id)
    {
        return m_id.CopyTo(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Id(HSTRING id)
    {
        return m_id.Set(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::TimeInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Separator(boolean* separator)
    {
        *separator = m_separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Separator(boolean separator)
    {
        m_separator = separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_isRequired;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_IsRequired(boolean isRequired)
    {
        m_isRequired = isRequired;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveCards::TimeInput> sharedTimeInput = std::make_shared<AdaptiveCards::TimeInput>();
        GetSharedModel(sharedTimeInput);

        return StringToJsonObject(sharedTimeInput->Serialize(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::GetSharedModel(std::shared_ptr<AdaptiveCards::TimeInput>& sharedModel) try
    {
        std::shared_ptr<AdaptiveCards::TimeInput> timeInput = std::make_shared<AdaptiveCards::TimeInput>();

        RETURN_IF_FAILED(SetSharedElementProperties(this, std::dynamic_pointer_cast<AdaptiveCards::BaseCardElement>(timeInput)));
        timeInput->SetIsRequired(m_isRequired);

        std::string max;
        RETURN_IF_FAILED(HStringToUTF8(m_max.Get(), max));
        timeInput->SetMax(max);

        std::string min;
        RETURN_IF_FAILED(HStringToUTF8(m_min.Get(), min));
        timeInput->SetMin(min);

        std::string placeholder;
        RETURN_IF_FAILED(HStringToUTF8(m_placeholder.Get(), placeholder));
        timeInput->SetPlaceholder(placeholder);

        std::string value;
        RETURN_IF_FAILED(HStringToUTF8(m_value.Get(), value));
        timeInput->SetValue(value);

        return S_OK;
    }CATCH_RETURN;
}}}
