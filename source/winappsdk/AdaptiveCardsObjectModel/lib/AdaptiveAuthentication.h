// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Authentication.h"

namespace AdaptiveCards::ObjectModel::WinUI3
{
    class DECLSPEC_UUID("8074FA48-AF80-4295-9BB3-D4827FA81CBE") AdaptiveAuthentication
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveAuthentication,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveAuthentication);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Authentication>& sharedRefresh);

        IFACEMETHODIMP get_Text(_Outptr_ HSTRING* text);
        IFACEMETHODIMP put_Text(_In_ HSTRING text);

        IFACEMETHODIMP get_ConnectionName(_Outptr_ HSTRING* connectionName);
        IFACEMETHODIMP put_ConnectionName(_In_ HSTRING connectionName);

        IFACEMETHODIMP get_TokenExchangeResource(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTokenExchangeResource** tokenExchangeResource);
        IFACEMETHODIMP put_TokenExchangeResource(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTokenExchangeResource* tokenExchangeResource);

        IFACEMETHODIMP get_Buttons(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveAuthCardButton*>** buttons);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::Authentication>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::Wrappers::HString m_text;
        Microsoft::WRL::Wrappers::HString m_connectionName;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTokenExchangeResource> m_tokenExchangeResource;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveAuthCardButton*>> m_buttons;
    };

    ActivatableClass(AdaptiveAuthentication);
}
