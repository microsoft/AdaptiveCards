// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveFactSet.h"
#include "AdaptiveFact.h"

#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::WinUI3
{
    AdaptiveFactSet::AdaptiveFactSet()
    {
        m_facts = Microsoft::WRL::Make<Vector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveFact*>>();
    }

    HRESULT AdaptiveFactSet::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::FactSet> factSet = std::make_shared<AdaptiveCards::FactSet>();
        return RuntimeClassInitialize(factSet);
    }
    CATCH_RETURN();

    HRESULT AdaptiveFactSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::FactSet>& sharedFactSet)
    try
    {
        if (sharedFactSet == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateFactsProjection(sharedFactSet->GetFacts(), m_facts.Get());

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedFactSet));
        return S_OK;
    }
    CATCH_RETURN();

    IFACEMETHODIMP AdaptiveFactSet::get_Facts(_COM_Outptr_ IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveFact*>** facts)
    {
        return m_facts.CopyTo(facts);
    }

    IFACEMETHODIMP AdaptiveFactSet::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::FactSet;
        return S_OK;
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveFactSet::GetSharedModel()
    {
        auto factSet = std::make_shared<AdaptiveCards::FactSet>();

        THROW_IF_FAILED(CopySharedElementProperties(*factSet));
        THROW_IF_FAILED(GenerateSharedFacts(m_facts.Get(), factSet->GetFacts()));

        return factSet;
    }
}
