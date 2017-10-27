#include "pch.h"
#include "AdaptiveFactSet.h"

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
        if (sharedFactSet == nullptr)
        {
            return E_INVALIDARG;
        }

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
    HRESULT AdaptiveFactSet::get_Spacing(ABI::AdaptiveCards::Uwp::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::Uwp::Spacing>(m_sharedFactSet->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::put_Spacing(ABI::AdaptiveCards::Uwp::Spacing spacing)
    {
        m_sharedFactSet->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::get_Separator(boolean* separator)
    {
        *separator = m_sharedFactSet->GetSeparator();
        return S_OK;

        //Issue #629 to make separator an object
        //return GenerateSeparatorProjection(m_sharedFactSet->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::put_Separator(boolean separator)
    {
        m_sharedFactSet->SetSeparator(separator);

        /*Issue #629 to make separator an object
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedFactSet->SetSeparator(sharedSeparator);
        */

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedFactSet->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedFactSet->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }
}}
