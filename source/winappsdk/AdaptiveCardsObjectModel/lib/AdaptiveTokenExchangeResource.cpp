// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTokenExchangeResource.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveTokenExchangeResource::RuntimeClassInitialize() noexcept
    {
        std::shared_ptr<AdaptiveCards::TokenExchangeResource> tokenExchangeResource =
            std::make_shared<AdaptiveCards::TokenExchangeResource>();
        return RuntimeClassInitialize(tokenExchangeResource);
    }

    HRESULT AdaptiveTokenExchangeResource::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TokenExchangeResource>& sharedTokenExchangeResource)
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedTokenExchangeResource->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedTokenExchangeResource->GetUri(), m_uri.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedTokenExchangeResource->GetProviderId(), m_providerId.GetAddressOf()));

        return S_OK;
    }

    HRESULT AdaptiveTokenExchangeResource::get_Id(_Outptr_ HSTRING* id) { return m_id.CopyTo(id); }

    HRESULT AdaptiveTokenExchangeResource::put_Id(_In_ HSTRING id) { return m_id.Set(id); }

    HRESULT AdaptiveTokenExchangeResource::get_Uri(_Outptr_ HSTRING* uri) { return m_uri.CopyTo(uri); }

    HRESULT AdaptiveTokenExchangeResource::put_Uri(_In_ HSTRING uri) { return m_uri.Set(uri); }

    HRESULT AdaptiveTokenExchangeResource::get_ProviderId(_Outptr_ HSTRING* providerId)
    {
        return m_providerId.CopyTo(providerId);
    }

    HRESULT AdaptiveTokenExchangeResource::put_ProviderId(_In_ HSTRING providerId)
    {
        return m_providerId.Set(providerId);
    }

    HRESULT AdaptiveTokenExchangeResource::GetSharedModel(std::shared_ptr<AdaptiveCards::TokenExchangeResource>& sharedModel)
    {
        std::shared_ptr<AdaptiveCards::TokenExchangeResource> tokenExchangeResource =
            std::make_shared<AdaptiveCards::TokenExchangeResource>();

        std::string id;
        RETURN_IF_FAILED(HStringToUTF8(m_id.Get(), id));
        tokenExchangeResource->SetId(id);

        std::string uri;
        RETURN_IF_FAILED(HStringToUTF8(m_uri.Get(), uri));
        tokenExchangeResource->SetUri(uri);

        std::string providerId;
        RETURN_IF_FAILED(HStringToUTF8(m_providerId.Get(), providerId));
        tokenExchangeResource->SetProviderId(providerId);

        sharedModel = std::move(tokenExchangeResource);
        return S_OK;
    }
}
