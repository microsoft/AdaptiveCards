// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "FactSet.h"
#include "AdaptiveFactSet.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("3aacc7c9-f600-4928-ae06-4cc21a83f4b3") AdaptiveFactSet : AdaptiveFactSetT<AdaptiveFactSet, ITypePeek>, AdaptiveCardElementBase
    {
        AdaptiveFactSet(const std::shared_ptr<::AdaptiveCards::FactSet>& sharedFactSet = std::make_shared<::AdaptiveCards::FactSet>());

        property<winrt::Windows::Foundation::Collections::IVector<Uwp::AdaptiveFact>> Facts;

        auto ElementType() { return ElementType::FactSet; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveFactSet : AdaptiveFactSetT<AdaptiveFactSet, implementation::AdaptiveFactSet>
    {
    };
}
