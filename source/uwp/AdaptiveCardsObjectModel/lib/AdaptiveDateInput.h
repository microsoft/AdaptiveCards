// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "DateInput.h"
#include "AdaptiveInputElement.h"
#include "AdaptiveDateInput.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("9aa05662-098b-4588-addb-af62378a8706") AdaptiveDateInput : AdaptiveDateInputT < AdaptiveDateInput, ITypePeek>,
        AdaptiveInputElementBase
    {
        AdaptiveDateInput(const std::shared_ptr<::AdaptiveCards::DateInput>& sharedDateInput = std::make_shared<::AdaptiveCards::DateInput>());

        auto ElementType() { return ElementType::DateInput; }

        property<hstring> Max;
        property<hstring> Min;
        property<hstring> Placeholder;
        property<hstring> Value;

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveDateInput : AdaptiveDateInputT<AdaptiveDateInput, implementation::AdaptiveDateInput>
    {
    };
}
