// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TokenExchangeResource.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class DECLSPEC_UUID("8074FA48-AF80-4295-9BB3-D4827FA81CBE") AdaptiveTokenExchangeResource
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTokenExchangeResource,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveTokenExchangeResource);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TokenExchangeResource>& sharedRefresh);

        IFACEMETHODIMP get_Id(_Outptr_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_Uri(_Outptr_ HSTRING* uri);
        IFACEMETHODIMP put_Uri(_In_ HSTRING uri);

        IFACEMETHODIMP get_ProviderId(_Outptr_ HSTRING* providerId);
        IFACEMETHODIMP put_ProviderId(_In_ HSTRING providerId);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::TokenExchangeResource>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::Wrappers::HString m_id;
        Microsoft::WRL::Wrappers::HString m_uri;
        Microsoft::WRL::Wrappers::HString m_providerId;
    };

    ActivatableClass(AdaptiveTokenExchangeResource);
}
