// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "UnknownElement.h"
#include "AdaptiveUnsupportedElement.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("e1ab7208-17bc-4fb6-b3c0-c1886987b4cf") AdaptiveUnsupportedElement
        : AdaptiveUnsupportedElementT<AdaptiveUnsupportedElement, ITypePeek>,
          AdaptiveCardElementBase
    {
        AdaptiveUnsupportedElement(const std::shared_ptr<::AdaptiveCards::UnknownElement>& sharedTextBlock =
                                       std::make_shared<::AdaptiveCards::UnknownElement>());

        auto ElementType() { return ElementType::Unsupported; }

        std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        std::string m_actualType;
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveUnsupportedElement : AdaptiveUnsupportedElementT<AdaptiveUnsupportedElement, implementation::AdaptiveUnsupportedElement>
    {
    };
}
