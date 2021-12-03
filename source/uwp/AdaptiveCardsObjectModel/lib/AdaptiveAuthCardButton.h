// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AuthCardButton.h"
#include "AdaptiveAuthCardButton.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("0DF8553F-E958-4E9C-897D-847691F1F3CC") AdaptiveAuthCardButton
        : AdaptiveAuthCardButtonT<AdaptiveAuthCardButton, ITypePeek>
    {
        AdaptiveAuthCardButton() : AdaptiveAuthCardButton(std::make_shared<::AdaptiveCards::AuthCardButton>()) {}
        AdaptiveAuthCardButton(std::shared_ptr<::AdaptiveCards::AuthCardButton> const& sharedAuthCardButton);

        property<hstring> Type;
        property<hstring> Title;
        property<hstring> Image;
        property<hstring> Value;

        std::shared_ptr<::AdaptiveCards::AuthCardButton> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveAuthCardButton : AdaptiveAuthCardButtonT<AdaptiveAuthCardButton, implementation::AdaptiveAuthCardButton>
    {
    };
}
