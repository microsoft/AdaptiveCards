#include "pch.h"
#include "AdaptiveFactSet.h"

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
    AdaptiveFactSet::AdaptiveFactSet()
    {
        m_facts = Microsoft::WRL::Make<Vector<IAdaptiveFact*>>();
    }

    HRESULT AdaptiveFactSet::RuntimeClassInitialize() noexcept try
    {
        m_sharedFactSet = std::make_shared<FactSet>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::FactSet>& sharedFactSet)
    {
        m_sharedFactSet = sharedFactSet;
        GenerateFactsProjection(m_sharedFactSet->GetFacts(), m_facts.Get());
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveFactSet::get_Facts(IVector<IAdaptiveFact*>** facts)
    {
        return m_facts.CopyTo(facts);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveFactSet::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::FactSet;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::get_Spacing(ABI::AdaptiveCards::XamlCardRenderer::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::XamlCardRenderer::Spacing>(m_sharedFactSet->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::put_Spacing(ABI::AdaptiveCards::XamlCardRenderer::Spacing spacing)
    {
        m_sharedFactSet->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::get_Separator(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator** separator)
    {
        return GenerateSeparatorProjection(m_sharedFactSet->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::put_Separator(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator* separator)
    {
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedFactSet->SetSeparator(sharedSeparator);

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedFactSet->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedFactSet->SetSpeak(out);
        return S_OK;
    }

}}
