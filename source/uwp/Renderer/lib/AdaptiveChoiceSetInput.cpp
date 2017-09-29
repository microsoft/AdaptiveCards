#include "pch.h"
#include "AdaptiveChoiceSetInput.h"

#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>
#include "AdaptiveCardRendererComponent.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace Uwp
{
    AdaptiveChoiceSetInput::AdaptiveChoiceSetInput()
    {
        m_choices = Microsoft::WRL::Make<Vector<IAdaptiveChoiceInput*>>();
    }

    HRESULT AdaptiveChoiceSetInput::RuntimeClassInitialize() noexcept try
    {
        m_sharedChoiceSetInput = std::make_shared<ChoiceSetInput>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ChoiceSetInput>& sharedChoiceSetInput)
    {
        if (sharedChoiceSetInput == nullptr)
        {
            return E_INVALIDARG;
        }

        m_sharedChoiceSetInput = sharedChoiceSetInput;
        GenerateInputChoicesProjection(m_sharedChoiceSetInput->GetChoices(), m_choices.Get());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_IsMultiSelect(boolean* isMultiSelect)
    {
        *isMultiSelect = m_sharedChoiceSetInput->GetIsMultiSelect();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_IsMultiSelect(boolean isMultiSelect)
    {
        m_sharedChoiceSetInput->SetIsMultiSelect(isMultiSelect);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_sharedChoiceSetInput->GetIsRequired();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_IsRequired(boolean isRequired)
    {
        m_sharedChoiceSetInput->SetIsRequired(isRequired);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_ChoiceSetStyle(ABI::AdaptiveCards::Uwp::ChoiceSetStyle* choiceSetStyle)
    {
        *choiceSetStyle = static_cast<ABI::AdaptiveCards::Uwp::ChoiceSetStyle>(m_sharedChoiceSetInput->GetChoiceSetStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_ChoiceSetStyle(ABI::AdaptiveCards::Uwp::ChoiceSetStyle choiceSetStyle)
    {
        m_sharedChoiceSetInput->SetChoiceSetStyle(static_cast<AdaptiveCards::ChoiceSetStyle>(choiceSetStyle));
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
        return UTF8ToHString(m_sharedChoiceSetInput->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedChoiceSetInput->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ChoiceSetInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_Spacing(ABI::AdaptiveCards::Uwp::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::Uwp::Spacing>(m_sharedChoiceSetInput->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_Spacing(ABI::AdaptiveCards::Uwp::Spacing spacing)
    {
        m_sharedChoiceSetInput->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_Separator(boolean* separator)
    {
        *separator = m_sharedChoiceSetInput->GetSeparator();
        return S_OK;

        //Issue #629 to make separator an object
        //return GenerateSeparatorProjection(m_sharedChoiceSetInput->GetSeparator(), separator); 
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_Separator(boolean separator)
    {
        m_sharedChoiceSetInput->SetSeparator(separator);

        /*Issue #629 to make separator an object
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedChoiceSetInput->SetSeparator(sharedSeparator);
        */

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }
}}
