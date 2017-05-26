#include "pch.h"
#include "AdaptiveInputChoiceSet.h"

#include "Util.h"
#include "Vector.h"
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
    AdaptiveInputChoiceSet::AdaptiveInputChoiceSet()
    {
        m_InputChoices = Microsoft::WRL::Make<Vector<IAdaptiveInputChoice*>>();
    }

    HRESULT AdaptiveInputChoiceSet::RuntimeClassInitialize() noexcept try
    {
        m_sharedInputChoiceSet = std::make_shared<InputChoiceSet>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::InputChoiceSet>& sharedInputChoiceSet)
    {
        m_sharedInputChoiceSet = sharedInputChoiceSet;
        GenerateInputChoicesProjection(m_sharedInputChoiceSet->GetChoices(), m_InputChoices.Get());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::get_IsMultiSelect(boolean* isMultiSelect)
    {
        *isMultiSelect = m_sharedInputChoiceSet->GetIsMultiSelect();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::put_IsMultiSelect(boolean isMultiSelect)
    {
        m_sharedInputChoiceSet->SetIsMultiSelect(isMultiSelect);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_sharedInputChoiceSet->GetIsRequired();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::put_IsRequired(boolean isRequired)
    {
        m_sharedInputChoiceSet->SetIsRequired(isRequired);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::get_ChoiceSetStyle(ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle* choiceSetStyle)
    {
        *choiceSetStyle = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle>(m_sharedInputChoiceSet->GetChoiceSetStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::put_ChoiceSetStyle(ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle choiceSetStyle)
    {
        m_sharedInputChoiceSet->SetChoiceSetStyle(static_cast<AdaptiveCards::ChoiceSetStyle>(choiceSetStyle));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::get_Choices(IVector<IAdaptiveInputChoice*>** inputChoices)
    {
        return m_InputChoices.CopyTo(inputChoices);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedInputChoiceSet->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedInputChoiceSet->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::InputChoiceSet;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::get_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation)
    {
        *separation = static_cast<ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle>(m_sharedInputChoiceSet->GetSeparationStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::put_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation)
    {
        m_sharedInputChoiceSet->SetSeparationStyle(static_cast<AdaptiveCards::SeparationStyle>(separation));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedInputChoiceSet->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputChoiceSet::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedInputChoiceSet->SetSpeak(out);
        return S_OK;
    }
}}
