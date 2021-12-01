// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFact.h"
#include "AdaptiveFact.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveFact::AdaptiveFact(const std::shared_ptr<::AdaptiveCards::Fact>& sharedFact)
    {
        Title = UTF8ToHString(sharedFact->GetTitle());
        Value = UTF8ToHString(sharedFact->GetValue());
        Language = UTF8ToHString(sharedFact->GetLanguage());
    }

    std::shared_ptr<::AdaptiveCards::Fact> AdaptiveFact::GetSharedModel()
    {
        auto fact = std::make_shared<::AdaptiveCards::Fact>();
        fact->SetTitle(HStringToUTF8(Title));
        fact->SetValue(HStringToUTF8(Value));
        fact->SetLanguage(HStringToUTF8(Language));
        return fact;
    }
}
