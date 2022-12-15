// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "NumberInput.h"
#include "AdaptiveInputElement.h"
#include "AdaptiveNumberInput.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("e54a7a83-8961-4745-8663-bbf5d45b6345") AdaptiveNumberInput : AdaptiveNumberInputT<AdaptiveNumberInput, ITypePeek>, AdaptiveInputElementBase
    {
        AdaptiveNumberInput(const std::shared_ptr<::AdaptiveCards::NumberInput>& sharedNumberInput =
                                std::make_shared<::AdaptiveCards::NumberInput>());

        // IAdaptiveNumberInput
        property<hstring> Placeholder;
        property_opt<double> Max;
        property_opt<double> Min;
        property_opt<double> Value;

        auto ElementType() { return ElementType::NumberInput; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveNumberInput : AdaptiveNumberInputT<AdaptiveNumberInput, implementation::AdaptiveNumberInput>
    {
    };
}
