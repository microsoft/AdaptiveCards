#include "pch.h"
#include "AdaptiveNumberInput.h"

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
    HRESULT AdaptiveNumberInput::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveCards::NumberInput> numberInput = std::make_shared<AdaptiveCards::NumberInput>();
        return RuntimeClassInitialize(numberInput);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::NumberInput>& sharedNumberInput) try
    {
        if (sharedNumberInput == nullptr)
        {
            return E_INVALIDARG;
        }

        m_min = sharedNumberInput->GetMin();
        m_max = sharedNumberInput->GetMax();
        m_value = sharedNumberInput->GetValue();
        RETURN_IF_FAILED(UTF8ToHString(sharedNumberInput->GetPlaceholder(), m_placeholder.GetAddressOf()));

        m_isRequired = sharedNumberInput->GetIsRequired();
        m_spacing = static_cast<ABI::AdaptiveCards::Rendering::Uwp::Spacing>(sharedNumberInput->GetSpacing());
        m_separator = sharedNumberInput->GetSeparator();
        RETURN_IF_FAILED(UTF8ToHString(sharedNumberInput->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedNumberInput->GetAdditionalProperties(), &m_additionalProperties));
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Placeholder(HSTRING* placeholder)
    {
        return m_placeholder.CopyTo(placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Placeholder(HSTRING placeholder)
    {
        return m_placeholder.Set(placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Value(INT32* value)
    {
        *value = m_value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Value(INT32 value)
    {
        m_value = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Max(INT32* max)
    {
        *max = m_max;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Max(INT32 max)
    {
        m_max = max;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Min(INT32* min)
    {
        *min = m_min;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Min(INT32 min)
    {
        m_min = min;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Id(HSTRING* id)
    {
        return m_id.CopyTo(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Id(HSTRING id)
    {
        return m_id.Set(id);
    }
    
    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::NumberInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Separator(boolean* separator)
    {
        *separator = m_separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Separator(boolean separator)
    {
        m_separator = separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_isRequired;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_IsRequired(boolean isRequired)
    {
        m_isRequired = isRequired;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveCards::NumberInput> sharedNumberInput = std::make_shared<AdaptiveCards::NumberInput>();
        GetSharedModel(sharedNumberInput);

        return StringToJsonObject(sharedNumberInput->Serialize(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::GetSharedModel(std::shared_ptr<AdaptiveCards::NumberInput>& sharedModel) try
    {
        std::shared_ptr<AdaptiveCards::NumberInput> numberInput = std::make_shared<AdaptiveCards::NumberInput>();

        RETURN_IF_FAILED(SetSharedElementProperties(this, std::dynamic_pointer_cast<AdaptiveCards::BaseCardElement>(numberInput)));
        numberInput->SetIsRequired(m_isRequired);

        numberInput->SetMin(m_min);
        numberInput->SetMax(m_max);
        numberInput->SetMax(m_value);

        std::string placeholder;
        RETURN_IF_FAILED(HStringToUTF8(m_placeholder.Get(), placeholder));
        numberInput->SetPlaceholder(placeholder);

        return S_OK;
    }CATCH_RETURN;
}}}
