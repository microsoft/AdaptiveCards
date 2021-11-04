// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Fact.h"
#include "AdaptiveFact.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("d37e5b66-2a5e-4a9e-b087-dbef5a1705b1") AdaptiveFact : AdaptiveFactT < AdaptiveFact, ITypePeek>
    {
        AdaptiveFact(const std::shared_ptr<::AdaptiveCards::Fact>& sharedFact = std::make_shared<::AdaptiveCards::Fact>());

        property<hstring> Title;
        property<hstring> Value;
        property<hstring> Language;

        auto ElementType() { return ElementType::Fact; }

        std::shared_ptr<::AdaptiveCards::Fact> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveFact : AdaptiveFactT<AdaptiveFact, implementation::AdaptiveFact>
    {
    };
}
