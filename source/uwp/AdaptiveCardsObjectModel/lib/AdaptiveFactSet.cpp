// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFactSet.h"
#include "AdaptiveFactSet.g.cpp"
#include "AdaptiveFact.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveFactSet::AdaptiveFactSet(const std::shared_ptr<::AdaptiveCards::FactSet>& sharedFactSet)
    {
        Facts = GenerateVectorProjection<implementation::AdaptiveFact>(sharedFactSet->GetFacts());
        InitializeBaseElement(sharedFactSet);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveFactSet::GetSharedModel()
    {
        auto factSet = std::make_shared<::AdaptiveCards::FactSet>();
        CopySharedElementProperties(*factSet);
        factSet->GetFacts() = GenerateSharedVector<implementation::AdaptiveFact, ::AdaptiveCards::Fact>(Facts.get());
        return factSet;
    }
}
