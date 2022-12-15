#include "pch.h"
#include "AdaptiveTokenExchangeResource.h"
#include "AdaptiveTokenExchangeResource.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveTokenExchangeResource::AdaptiveTokenExchangeResource(const std::shared_ptr<::AdaptiveCards::TokenExchangeResource>& sharedRefresh)
    {
        Id = UTF8ToHString(sharedRefresh->GetId());
        Uri = UTF8ToHString(sharedRefresh->GetUri());
        ProviderId = UTF8ToHString(sharedRefresh->GetProviderId());
    }

    std::shared_ptr<::AdaptiveCards::TokenExchangeResource> AdaptiveTokenExchangeResource::GetSharedModel()
    {
        auto tokenExchangeResource = std::make_shared<::AdaptiveCards::TokenExchangeResource>();
        tokenExchangeResource->SetId(HStringToUTF8(Id));
        tokenExchangeResource->SetUri(HStringToUTF8(Uri));
        tokenExchangeResource->SetProviderId(HStringToUTF8(ProviderId));
        return tokenExchangeResource;
    }
}
