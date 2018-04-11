#include "pch.h"
#include "AdaptiveFactSet.h"

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
    AdaptiveFactSet::AdaptiveFactSet()
    {
        m_facts = Microsoft::WRL::Make<Vector<IAdaptiveFact*>>();
    }

    HRESULT AdaptiveFactSet::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::FactSet> factSet = std::make_shared<AdaptiveSharedNamespace::FactSet>();
        return RuntimeClassInitialize(factSet);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::FactSet>& sharedFactSet) try
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

    HRESULT AdaptiveFactSet::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::FactSet> factSet = std::make_shared<AdaptiveSharedNamespace::FactSet>();

        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseCardElement>(factSet)));
        RETURN_IF_FAILED(GenerateSharedFacts(m_facts.Get(), factSet->GetFacts()));

        sharedModel = factSet;

        return S_OK;
    }CATCH_RETURN;
AdaptiveNamespaceEnd
