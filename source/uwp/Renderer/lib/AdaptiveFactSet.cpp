#include "pch.h"
#include "AdaptiveFactSet.h"

#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    AdaptiveFactSet::AdaptiveFactSet()
    {
        m_facts = Microsoft::WRL::Make<Vector<IAdaptiveFact*>>();
    }

    HRESULT AdaptiveFactSet::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveCards::FactSet> factSet = std::make_shared<AdaptiveCards::FactSet>();
        return RuntimeClassInitialize(factSet);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::FactSet>& sharedFactSet) try
    {
        if (sharedFactSet == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateFactsProjection(sharedFactSet->GetFacts(), m_facts.Get());
        
        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedFactSet));
        return S_OK;
    } CATCH_RETURN;

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

    HRESULT AdaptiveFactSet::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveCards::FactSet> factSet = std::make_shared<AdaptiveCards::FactSet>();

        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveCards::BaseCardElement>(factSet)));
        RETURN_IF_FAILED(GenerateSharedFacts(m_facts.Get(), factSet->GetFacts()));

        sharedModel = factSet;

        return S_OK;
    }CATCH_RETURN;
}}}
