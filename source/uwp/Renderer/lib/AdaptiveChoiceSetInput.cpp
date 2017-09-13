#include "pch.h"
#include "AdaptiveChoiceSetInput.h"

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
    HRESULT AdaptiveChoiceSetInput::get_ChoiceSetStyle(ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle* choiceSetStyle)
    {
        *choiceSetStyle = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle>(m_sharedChoiceSetInput->GetChoiceSetStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_ChoiceSetStyle(ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle choiceSetStyle)
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
    HRESULT AdaptiveChoiceSetInput::get_Spacing(ABI::AdaptiveCards::XamlCardRenderer::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::XamlCardRenderer::Spacing>(m_sharedChoiceSetInput->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_Spacing(ABI::AdaptiveCards::XamlCardRenderer::Spacing spacing)
    {
        m_sharedChoiceSetInput->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_Separator(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator** separator)
    {
        return GenerateSeparatorProjection(m_sharedChoiceSetInput->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_Separator(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator* separator)
    {
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedChoiceSetInput->SetSeparator(sharedSeparator);

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedChoiceSetInput->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInput::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedChoiceSetInput->SetSpeak(out);
        return S_OK;
    }
}}
