#include "pch.h"
#include "AdaptiveChoiceSetInput.h"

#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

AdaptiveNamespaceStart
    AdaptiveChoiceSetInput::AdaptiveChoiceSetInput()
    {
        m_choices = Microsoft::WRL::Make<Vector<IAdaptiveChoiceInput*>>();
    }

    HRESULT AdaptiveChoiceSetInput::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ChoiceSetInput> choiceSet = std::make_shared<AdaptiveSharedNamespace::ChoiceSetInput>();
        return RuntimeClassInitialize(choiceSet);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::ChoiceSetInput>& sharedChoiceSetInput)
    {
        if (sharedChoiceSetInput == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateInputChoicesProjection(sharedChoiceSetInput->GetChoices(), m_choices.Get());

        m_isRequired = sharedChoiceSetInput->GetIsRequired();
        m_isMultiSelect = sharedChoiceSetInput->GetIsMultiSelect();
        m_choiceSetStyle = static_cast<ABI::AdaptiveNamespace::ChoiceSetStyle>(sharedChoiceSetInput->GetChoiceSetStyle());
        RETURN_IF_FAILED(UTF8ToHString(sharedChoiceSetInput->GetValue(), m_value.GetAddressOf()));

        m_spacing = static_cast<ABI::AdaptiveNamespace::Spacing>(sharedChoiceSetInput->GetSpacing());
        m_separator = sharedChoiceSetInput->GetSeparator();
        RETURN_IF_FAILED(UTF8ToHString(sharedChoiceSetInput->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedChoiceSetInput->GetAdditionalProperties(), &m_additionalProperties));

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_IsMultiSelect(boolean* isMultiSelect)
    {
        *isMultiSelect = m_isMultiSelect;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_IsMultiSelect(boolean isMultiSelect)
    {
        m_isMultiSelect = isMultiSelect;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_isRequired;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_IsRequired(boolean isRequired)
    {
        m_isRequired = isRequired;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_ChoiceSetStyle(ABI::AdaptiveNamespace::ChoiceSetStyle* choiceSetStyle)
    {
        *choiceSetStyle = m_choiceSetStyle;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_ChoiceSetStyle(ABI::AdaptiveNamespace::ChoiceSetStyle choiceSetStyle)
    {
        m_choiceSetStyle = choiceSetStyle;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_Choices(IVector<IAdaptiveChoiceInput*>** choices)
    {
        return m_choices.CopyTo(choices);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_Id(HSTRING* id)
    {
        return m_id.CopyTo(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_Id(HSTRING id)
    {
        return m_id.Set(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ChoiceSetInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_Spacing(ABI::AdaptiveNamespace::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_Spacing(ABI::AdaptiveNamespace::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_Separator(boolean* separator)
    {
        *separator = m_separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_Separator(boolean separator)
    {
        m_separator = separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }    
    
    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveSharedNamespace::ChoiceSetInput> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::ChoiceSetInput>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ChoiceSetInput> choiceSet = std::make_shared<AdaptiveSharedNamespace::ChoiceSetInput>();

        RETURN_IF_FAILED(SetSharedElementProperties(this, std::AdaptivePointerCast<AdaptiveSharedNamespace::BaseCardElement>(choiceSet)));

        choiceSet->SetChoiceSetStyle(static_cast<AdaptiveSharedNamespace::ChoiceSetStyle>(m_choiceSetStyle));
        choiceSet->SetIsMultiSelect(m_isMultiSelect);
        choiceSet->SetIsRequired(m_isRequired);

        RETURN_IF_FAILED(GenerateSharedChoices(m_choices.Get(), choiceSet->GetChoices()));

        sharedModel = choiceSet;
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveChoiceSetInput::get_Value(HSTRING * value)
    {
        m_value.CopyTo(value);
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInput::put_Value(HSTRING value)
    {
        m_value.Set(value);
        return S_OK;
    }
AdaptiveNamespaceEnd
