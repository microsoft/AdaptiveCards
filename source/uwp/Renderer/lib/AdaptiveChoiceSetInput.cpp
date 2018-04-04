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
    HRESULT AdaptiveChoiceSetInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::ChoiceSetInput>& sharedChoiceSetInput) try
    {
        if (sharedChoiceSetInput == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateInputChoicesProjection(sharedChoiceSetInput->GetChoices(), m_choices.Get());

        m_isMultiSelect = sharedChoiceSetInput->GetIsMultiSelect();
        m_choiceSetStyle = static_cast<ABI::AdaptiveNamespace::ChoiceSetStyle>(sharedChoiceSetInput->GetChoiceSetStyle());
        RETURN_IF_FAILED(UTF8ToHString(sharedChoiceSetInput->GetValue(), m_value.GetAddressOf()));

        InitializeBaseElement(std::static_pointer_cast<BaseInputElement>(sharedChoiceSetInput));
        return S_OK;
    } CATCH_RETURN;

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
    HRESULT AdaptiveChoiceSetInput::get_Value(HSTRING * value)
    {
        m_value.CopyTo(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_Value(HSTRING value)
    {
        m_value.Set(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ChoiceSetInput;
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInput::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ChoiceSetInput> choiceSet = std::make_shared<AdaptiveSharedNamespace::ChoiceSetInput>();

        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseInputElement>(choiceSet)));

        choiceSet->SetChoiceSetStyle(static_cast<AdaptiveSharedNamespace::ChoiceSetStyle>(m_choiceSetStyle));
        choiceSet->SetIsMultiSelect(m_isMultiSelect);

        RETURN_IF_FAILED(GenerateSharedChoices(m_choices.Get(), choiceSet->GetChoices()));

        sharedModel = choiceSet;
        return S_OK;
    } CATCH_RETURN;

AdaptiveNamespaceEnd
