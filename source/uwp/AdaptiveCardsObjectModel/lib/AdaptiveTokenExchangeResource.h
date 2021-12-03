// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "TokenExchangeResource.h"
#include "AdaptiveTokenExchangeResource.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("8074FA48-AF80-4295-9BB3-D4827FA81CBE") AdaptiveTokenExchangeResource
        : AdaptiveTokenExchangeResourceT<AdaptiveTokenExchangeResource, ITypePeek>
    {
        AdaptiveTokenExchangeResource() :
            AdaptiveTokenExchangeResource(std::make_shared<::AdaptiveCards::TokenExchangeResource>())
        {
        }

        AdaptiveTokenExchangeResource(const std::shared_ptr<::AdaptiveCards::TokenExchangeResource>& sharedRefresh);

        property<hstring> Id;
        property<hstring> Uri;
        property<hstring> ProviderId;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        std::shared_ptr<::AdaptiveCards::TokenExchangeResource> GetSharedModel();
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveTokenExchangeResource : AdaptiveTokenExchangeResourceT<AdaptiveTokenExchangeResource, implementation::AdaptiveTokenExchangeResource>
    {
    };
}
