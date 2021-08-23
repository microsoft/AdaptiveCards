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

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
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
