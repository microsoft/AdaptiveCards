// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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

namespace AdaptiveNamespace
{
    AdaptiveFactSet::AdaptiveFactSet() { m_facts = Microsoft::WRL::Make<Vector<AdaptiveFact*>>(); }

    HRESULT AdaptiveFactSet::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::FactSet> factSet = std::make_shared<AdaptiveSharedNamespace::FactSet>();
        return RuntimeClassInitialize(factSet);
    }
    CATCH_RETURN;

    HRESULT AdaptiveFactSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::FactSet>& sharedFactSet)
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
    CATCH_RETURN;

    IFACEMETHODIMP AdaptiveFactSet::get_Facts(_COM_Outptr_ IVector<AdaptiveFact*>** facts)
    {
        return m_facts.CopyTo(facts);
    }

    IFACEMETHODIMP AdaptiveFactSet::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::FactSet;
        return S_OK;
    }

    HRESULT AdaptiveFactSet::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::FactSet> factSet = std::make_shared<AdaptiveSharedNamespace::FactSet>();

        RETURN_IF_FAILED(CopySharedElementProperties(*factSet));
        RETURN_IF_FAILED(GenerateSharedFacts(m_facts.Get(), factSet->GetFacts()));

        sharedModel = std::move(factSet);

        return S_OK;
    }
    CATCH_RETURN;
}
