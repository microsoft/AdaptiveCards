// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ToggleInput.h"
#include "AdaptiveInputElement.h"
#include "AdaptiveToggleInput.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("502edea9-72fd-4856-a89e-54565181bed8") AdaptiveToggleInput : AdaptiveToggleInputT<AdaptiveToggleInput, ITypePeek>, AdaptiveInputElementBase
    {
        AdaptiveToggleInput(const std::shared_ptr<::AdaptiveCards::ToggleInput>& sharedToggleInput =
                                std::make_shared<::AdaptiveCards::ToggleInput>());

        property<hstring> Title;
        property<hstring> Value;
        property<hstring> ValueOn;
        property<hstring> ValueOff;
        property<bool> Wrap;

        // IAdaptiveCardElement
        auto ElementType() { return ElementType::ToggleInput; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveToggleInput : AdaptiveToggleInputT<AdaptiveToggleInput, implementation::AdaptiveToggleInput>
    {
    };
}
